#include "control.h"
#define OCPSET 150 //ms  
#define OCPBACK 450 //ms   

#define T PTPER
#define NSTART 10
#define VMIN 0x6e00
#define VABSMIN 0x6800
#define BOOTLOADER_FLAG_ADDRESS 0x17fe //t Musí být shodné s aplikací

volatile unsigned int __attribute__((address(BOOTLOADER_FLAG_ADDRESS),persistent)) bootloader_flag;//t

// Allocate and reserve a page of flash for this test to use.  The compiler/linker will reserve this for data and not place any code here.
 __prog__  uint16_t flashPage[(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS/2)] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)))\
         ={MAXCYC,FORCERATIO,SETSVOLA,HOLDTIME,RETIME,MAXCLOSE, GREASECYCLES,GREASEREVS,CURBRAKE,CYCLES};//declaration of constants to program flash
 __prog__  uint16_t flashPage2[(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS/2)] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
uint16_t start,clamp,released, curax, curcomp,nforces,milisec;
float voltage, voltmotor,curmotor, delta;
const float resmotor= 0.3;
unil dto,cycax;
adcfilter curr,trim,volt, currslow;
uint16_t ocp,timgled,shinegled=2,darkgled=600,j,reduce;
int16_t current,currentslow, curmes, startcyco, startmem,starcomp,compar;
uint32_t ms;
uint32_t flash_addr, flash_addr2,k24;
bool FINCYC,FLREG;
int16_t vel,slopevel,endvel,forvel,difvel; 
 // sets pointers to  holding registers of Modbus
 int16_t *const ptspace= (int16_t *)&HOLDREGSR[0].W;
 uint16_t *const ptforat =(uint16_t *)&HOLDREGSR[1].W;
 sets *const ptsets=     (sets *)&HOLDREGSR[2].W;
 uint16_t *const ptsecforce=(uint16_t *)&HOLDREGSR[3].W;
 uint16_t * const ptsecnofo=(uint16_t *)&HOLDREGSR[4].W;
 int16_t * const ptclose= (int16_t *)&HOLDREGSR[5].W;
  int16_t * const ptcureal=(int16_t *)&HOLDREGSR[8].W;
 int32_t * const ptcycles=(int32_t *)&HOLDREGSR[9].W;
  
 int16_t ReduceForce(uint16_t value, uint16_t redu)
 {
     int16_t retval;
     if(redu != 0)//no necessary         
        retval = ((-redu) & 0x0f)*(value>>4);// endvel = (0x10- (reduce & 0x0f))*(auxvolt>>4);
     else 
        retval= value;             //increase of current after impact
     return retval;
 }

void setReady(void)
{
  state= READY;
  vel= 0;
  endvel=0;
  slopevel= 0;
  ec.Run= false;
  ForceCommutation();
}

void setAway(void)
{
    shinegled=100;  
    darkgled=400;
    ms=0;
    state= AWAY;
    startcycles=0;
    startmem= startcycles;
    starcomp= startcycles;
    ec.SlowToBrake= false;
    ocp= OCPBACK;
    ec.Run= true;
    vel= -200;
    endvel=-1000;
    slopevel= -6;
    ForceCommutation();
}

void setInto(void)
{
                    shinegled=200;  
                    darkgled=800;
                    ms=0;
                    state= INTO;
                    ec.SlowToBrake= false;
                    vel= 200;
                    endvel=1000;        //                    pwmvolt(1000);//maximum velocity MDC=0.94*PTPER 
                    slopevel= 20;   //set ramp
                    IC4CON1bits.ICM=0;//set capture zero
                    IC3CON1bits.ICM=0;
                    TMR3HLD=0;
                    TMR2=0;
                    IC4CON1bits.ICM=1;
                    IC3CON1bits.ICM=1;
                    startmem= startcycles;
                    starcomp= startcycles; 
                    compar = ReduceForce(*ptcureal, reduce);                 
                    ocp= OCPSET;        //blocked motor stop by overcurrent for ocp ms
                    ec.Run= true;
                    ForceCommutation();
                  
}


void setHold(void)
{
   ec.SlowToBrake= false;
   forvel= ReduceForce(*ptforat, reduce);
  endvel= forvel;//final force
  slopevel= 6;//-6;
  ms=0;
  state= HOLD; 
  clamp=0;
  ec.Run= true; //t
  ForceCommutation();   //t
}

void setRelease(void)
{
    clamp=0;
    shinegled=800;  
    darkgled=200;
    ec.SlowToBrake= false;//t
    ms=0;
    state=RELEASE;
    vel= 0;
    endvel=0;
    slopevel=0;
    ec.Run= false;
    ForceCommutation();
}

inline void interf()//program link between reading and writing the modbus protocol
{    
    switch(mbs.funCode)
    {
       case 0x10:  
        k24= FLASH_ReadWord24(flash_addr2);
        if(k24 & 0x00800000)
            k24 |=0xff000000;
        if(*ptcycles != (int32_t) k24)
           writeflashDW(flash_addr2,*ptcycles,0);
        else 
            if(mbs.startAdr.W==ADR0HOLDREG+0x10)        
            {
                reduce= HOLDREGSR[0x10].W;
            }     
        else
        {
           bootloader_flag = HOLDREGSR[11].W;   //t
           HOLDREGSR[11].W=0;                   //t
           writeflash(flash_addr,(uint16_t *)(&(HOLDREGSR[0].W)));
           ec.INV= ptsets->NEGHALL;
           ec.Left= ptsets->LEFT;
        }
        break;
        case 4: 
            err.W=0;
            break;
        default:
            break;
  }  
    
    
}

void writrev(unil trev)  //write revolving time into modbus registers
{
      if(ec.Current_Direction== CCW)
          trev.il= -trev.il;
      INP[2] = trev.l;// write it to Modbus input registers
      INP[3] = trev.h;
}

 void correction()//P current regulator
{
    difvel= forvel- (((currentslow>>6)*50)>>6);
    endvel+= (difvel>>1); //t
            
}

void __attribute__ ((weak)) TMR1_CallBack(void)//1ms tick
{
    if(start>0)     //delay after starting the program
        start--;
    if(ocp>0)       //monitoring the maximum time without changing the Hall sensors of the motor position
        ocp--;
            // green LED flashing times 
    timgled++;     //time of green LED shine/dark 
    if(GRE== DARK)
    {
        if(timgled >= darkgled)
        {
          timgled=0;
          GRE= SHINE;
        }
    }
    else
    {
        if(timgled >= shinegled)
        {
          timgled=0;
          GRE= DARK;            
        }
    }
    timwuart++;
    buttonfilt();
            //switch button filtering
   if((milisec & 0x3f)==0)  //64ms 
       FLREG=true;
   milisec++;
   milisec &= 0x3ff;//=1024ms
   if(milisec==0)//~1s
   {
     if(state==HOLD)
     {
       clamp++;
     }
     else if(state==RELEASE)
     {  if(ptsets->AUTOTEST && (released > *ptsecforce))
        {
         released=0;
         setAway();
        }
        else
         released++; 
     }
     else if(state==READY)
     {
         if(ptsets->AUTOTEST) 
         {
             if(released > (*ptsecforce*2))
             {
                 released=0;
                 setInto();
             }
             else 
                 released++;             
         }
         else
             released=0;
     }
   }

   if(dt.hl < 400000)
   {
       _IC1IE= true;
       _IC2IE= true;
       _IC3IE= true;
   }
   else if(dt.hl > 600000)
   {
       _IC1IE= false;
       _IC2IE= false;
       _IC3IE= false;
       ForceCommutation();
       IC1nucleo();
       IC2nucleo();
       IC3nucleo();
   }

   if(ec.ComutPh1)
   {
    ec.ComutPh1= false;
   }
   if(ec.ComutPh2)
   {
    ec.ComutPh2= false;
   }
   if(ec.ComutPh3)
   {
    ec.ComutPh3= false;
    IEC2bits.IC3IE = false;// disable interrupt from Hall sensors  
    {          
             dto.hl=dt.hl;
             writrev(dt);
             IEC2bits.IC3IE = true; //enable interrupt from Hall sensors            
             //if(state == INTO)
             if(ec.Run)
             {
                 //slow down of motor revolution
                   if(((int32_t)(dt.hl-dto.hl) > SLOWMAX)&&(abs(startcycles-starcomp) >= 24))//t
                   {
                       shinegled=200;
                       darkgled=200;
                       err.SlowPress = true;
                       ec.SlowToBrake= true;
                   } 
                    
             }
    }
    IEC2bits.IC3IE = true;  //enable interrupt from Hall sensors 
   }
   if(startcyco== startcycles)//no motor revolution
   { if(ms>=100)  
     {
        if((state== INTO)||(state== AWAY))
          err.Winding= true;
     }
     if(ms == 100) 
     {
      ms++;
      dto.hl=dt.hl;
      dt.hl= 0x7fffffff;//if 100ms no Hall sensor edge, motor is used not to move 
      writrev(dt);//write revolving time to Modbus input registers
     
     }
     else if(ms < 100)
         ms++;
   }
   else
   {
       ms=0;
       INP[1] = startcycles;//write distance to Modbus input register
   }
   vel=ramp(vel, endvel,slopevel);//on slopes(pointer to actual value, final value, absolute slope)
     pwmvolt(vel);              //set ratio of pwm output; max. ratio is +/- 1000 of 1024  
   startcyco= startcycles;
   cycax.il= *ptcycles;
   INPREGS[0].W= cycax.l;
   INPREGS[1].W= cycax.h;
   inmbmem();
}

inline void compcurrent(void)//compare current
{    
    if(((current>>6) > compar)&&(ocp == 0))  
    {
       {
                        shinegled=100;
                        darkgled=100;
                        ec.SlowToBrake= true;
                        if(state == INTO)
                            setHold();                           
      }
    } 
}

void __attribute__ ((weak)) ADC1_CallBack(void)
{
       volt.adc =  ADC1BUF1;
    trim.adc =  ADC1BUF0;
    curr.adc =  ADC1BUF3;
    currslow.adc =  ADC1BUF3;
    Filt(&curr);
    Filt(&trim);
    Filt(&volt);
    Filt(&currslow);
    if(volt.filter < VMIN)
        err.WeakPower= true;
    if(volt.filter < VABSMIN)
        err.LowPower= true;
    switch(state)
    {
        case  VOLTON:   
            curcomp=currslow.filter;// current compensation
         break;
        case  READY:   
         curcomp=currslow.filter;// current compensation   
         break;
        case  RELEASE:   
             curcomp=currslow.filter;// current compensation
         break;
        case  HOLD:   
          break;
        case  INTO:   
          break;
        case  AWAY:   
          break;
        default:
         pwmvolt(0);//stop
         break;
    }
    current= curr.filter-curcomp;
    currentslow= currslow.filter-curcomp;
    compcurrent();
    INP[0] = (current >> 6);// writes parameters to  input registers
    INP[4] = (volt.filter >> 6);
    err.State= state;//t
    INP[5] = err.W;
    
}

inline void iniControl(void)// initialization at program start
{
 inivarifcs();
 start=NSTART;
  cfgModbus();
  flash_addr = FLASH_GetErasePageAddress((uint32_t)flashPage);
  flash_addr2 = FLASH_GetErasePageAddress((uint32_t)flashPage2);
  FLASH_Unlock(FLASH_UNLOCK_KEY);
  for(int jn=0;jn<NREGS;jn++)
  {
      HOLDREGSR[jn].W = (int16_t) FLASH_ReadWord16(flash_addr+ jn*2U);
  }
  //ptsets->NEGHALL=0;//t
  ec.INV= ptsets->NEGHALL;
  ec.Left= ptsets->LEFT;
  *ptcycles= (int32_t) FLASH_ReadWord24(flash_addr2);
  if (*ptcycles & 0x00800000)*ptcycles |= 0xff000000;
  curr.kfil=0x1000;//0.0625
  trim.kfil=0x800; //0.03125
  volt.kfil=0x100; //0.0039
  currslow.kfil=0x100; //0.0039
  CVR2CONbits.CVR = CURRMAX + 0x40;//t     //current comparator limit
  err.WatchDog= ((RCON & 0b1100001001010000)!= 0);
  RCONbits.WDTO= false;
  RCONbits.TRAPR= false;
  RCONbits.SWR= false;
  RCONbits.IOPUWR= false;
  //RCONbits.EXTR= false;
  RCONbits.CM= false;
  dt.hl=0x7fffffff;
  _IC1IE= false;//t
  _IC2IE= false;
  _IC3IE= false;
}

inline void Control(void)
{
      if(state== VOLTON)
      {
        if(start==0)//delay of ready state
        {
            shinegled=10; 
            darkgled=990;
            setReady();
        }
      }
      else if(controls.SWREAL)  //rise edge of switch
      {
        controls.SWREAL= false;
  //      bootloader_flag = 0xA5A5;//t
        {
           if(!ptsets->AUTOTEST)
            switch(state)
            {                
                case READY:
                    setInto();
                 break;               
                 case AWAY:
                    setInto();
                 break;
                   default:
                    break;
            }
            
        }
      }
      else if(controls.SWUNRE)  //falling edge of switch
      {
        controls.SWUNRE= false;
        if(!ptsets->AUTOTEST)
          switch(state)
            {              
               case INTO:
                 setAway();
                 break;
               case RELEASE:
                 nforces++;
                 setAway();
                 FINCYC=true;
                 break;
               case HOLD:
                 nforces++;
                 setAway();  
                 FINCYC=true;
                 break;
               default:
                  break;
             } 
      }         
      switch(state)
      {   
          case INTO:          
            if(ec.SlowToBrake)
            {
                setHold();
              
            }
            else if((startcycles-startmem) > *ptclose)
            {
                err.LowPressure= true;
                setRelease(); 
            }
          break;
          case HOLD:
            if(clamp> *ptsecforce)   //s after HOLD time switch to RELEASE
            {
                setRelease();               
            }
            else 
            if (FLREG)
            {
                FLREG=false;
                correction();
            }
          break;
          case RELEASE:
            if(released > *ptsecnofo)
            {
              released=0;
              setHold();           
            }
            break;
          case AWAY:
            if(ec.SlowToBrake)
            {
              ec.SlowToBrake= false;
              shinegled=500; 
              darkgled=500;
              err.Opening= true;
              setReady();  
            }
            else  if((startcycles-startmem) < -*ptspace)
            {
                if(ptsets->AUTOTEST)
                    FINCYC=true;
                shinegled=200; 
                darkgled=800;
                setReady();  
            }
          break;
          case READY:
            if(ec.SlowToBrake)
            {
              ec.SlowToBrake= false;
            }
            if(FINCYC)//flag of finish of cycle
            {
             FINCYC=false;
             (*ptcycles)++;
              writeflashDW(flash_addr2,*ptcycles,0);
            }
          break;
       
          default:
              ec.SlowToBrake= false;
          break;
      } 
}

