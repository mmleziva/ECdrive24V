#include "ecmotor.h"

bint h;
errors err;
union
{
    struct {
      uint16_t OSYNC:1;
      uint16_t SWAP:1;
      uint16_t CLDAT:2;
      uint16_t FLTDAT:2;
      uint16_t OVRDAT:2;
      uint16_t OVRENL:1;
      uint16_t OVRENH:1;
      uint16_t PMOD:2;
      uint16_t POLL:1;
      uint16_t POLH:1;
      uint16_t PENL:1;
      uint16_t PENH:1;
    };
    struct {
      uint16_t :2;
      uint16_t CLDAT0:1;
      uint16_t CLDAT1:1;
      uint16_t FLTDAT0:1;
      uint16_t FLTDAT1:1;
      uint16_t OVRDAT0:1;
      uint16_t OVRDAT1:1;
      uint16_t OVREN:2;
      uint16_t PMOD0:1;
      uint16_t PMOD1:1;
      uint16_t POL:2;
    };
    uint16_t i;
}io1,io2,io3;


unsigned int Hall(void)           //return switched hall sensors for motor 1
{
    if(ec.INV)
    {
        h.b0=  ! _RA1;
        h.b1=  ! _RB0;
        h.b2=  ! _RB2;
    }
    else
    {
         h.b0= _RA1;
         h.b1= _RB0;
         h.b2= _RB2;
    }
    return h.i;
}
int state;

// Constants used for properly energizing the motor depending on the 
// rotor's position

//int ControlOutput = 0;	// Controller output, used as a voltage output, 
                            // use its sign for the required direction
int MeasuredSpeed;	// Actual speed for the PID 
                            // controller, that will generate the error
//unsigned char Required_Direction;	// Required mechanical motor direction of 
                                    // rotation, will have the same sign as the
									// ControlOutput variable from the Speed 
                                    // Controller
//unsigned int Sector, Secorr;  // This variables holds present sector value, which is 
                      // the rotor position
unsigned int Sector;  // This variables holds present sector value, which is 
                      // the rotor position
unsigned int LastSector; // This variable holds the last sector value. This 
                         // is critical to filter slow slew rate on the Hall
                         // eff ect sensors hardware


const char SectorTable[] = {-1,1,3,2,5,0,4,-1};

unsigned int HallValue;
int tic1,tic2,tic3,tax3,tay3;
unil dt,t1,t2;
int16_t startcycles;
motorbits ec;

void ForceCommutation(void)
{
  //  bit hs;
	HallValue = Hall();
    if(Sector== (LastSector+1)%6)
        ec.Current_Direction= CW;
    else if((Sector+1)%6== LastSector)
        ec.Current_Direction= CCW;
    else ec.Current_Direction= ec.Required_Direction;
    LastSector= Sector;
    Sector = SectorTable[HallValue];	// Get Sector from table
    io1.i= IOCON1;
    io2.i= IOCON2;
    io3.i= IOCON3;
    if(Sector == -1)	// If the sector is invalid don't do anything
	{
          err.Halls=true;
    }
    else
    if(ec.Run)
    {	  
        switch((Sector + ec.Required_Direction*3)%6)
        {
            case 0:         //+-0
                io1.OVREN=0;
                io1.POL=0;
                io1.CLDAT=2;
                io1.FLTDAT=2;
                io2.OVREN=0;
                io2.POL=3;
                io2.CLDAT=1;
                io2.FLTDAT=1;
                io3.OVREN=3;  
                io3.POL=0;
                io3.CLDAT=2;
                io3.FLTDAT=2;
            break;    
            case 1:         //+0-
                io1.OVREN=0;
                io1.POL=0;
                io1.CLDAT=2;
                io1.FLTDAT=2;
                io2.OVREN=3;
                io2.POL=0;   
                io2.CLDAT=2;
                io2.FLTDAT=2;
                io3.OVREN=0;
                io3.POL=3;
                io3.CLDAT=1;
                io3.FLTDAT=1;
            break;    
            case 2:         //0+-
                io1.OVREN=3;
                io1.POL=0; 
                io1.CLDAT=2;
                io1.FLTDAT=2;
                io2.OVREN=0;                
                io2.POL=0;
                io2.CLDAT=2;
                io2.FLTDAT=2;
                io3.OVREN=0;
                io3.POL=3;
                io3.CLDAT=1;
                io3.FLTDAT=1;
            break;    
            case 3:         //-+0
                io1.OVREN=0;
                io1.POL=3;
                io1.CLDAT=1;
                io1.FLTDAT=1;
                io2.OVREN=0;
                io2.POL=0;
                io2.CLDAT=2;
                io2.FLTDAT=2;
                io3.OVREN=3;
                io3.POL=0;  
                io3.CLDAT=2;
                io3.FLTDAT=2;
            break;    
            case 4:         //-0+
                io1.OVREN=0;
                io1.POL=3;
                io1.CLDAT=1;
                io1.FLTDAT=1;
                io2.OVREN=3;
                io2.POL=0;
                io2.CLDAT=2;
                io2.FLTDAT=2;
                io3.OVREN=0;
                io3.POL=0;
                io3.CLDAT=2;
                io3.FLTDAT=2;
            break;    
            case 5:         //0-+
                io1.OVREN=3;
                io1.POL=0;
                io1.CLDAT=2;
                io1.FLTDAT=2;
                io2.OVREN=0;
                io2.POL=3;
                io2.CLDAT=1;
                io2.FLTDAT=1;
                io3.OVREN=0;
                io3.POL=0;
                io3.CLDAT=2;
                io3.FLTDAT=2;
            break;    
        }      
        IOCON1= io1.i;
        IOCON2= io2.i;
        IOCON3= io3.i; 
   //     err.Halls=false;    
	}
    else        //stop
    {
        IOCON1= 0xC7A0;
        IOCON2= 0xC7A0;
        IOCON3= 0xC7A0; 
   //     err.Halls=false;
    }
	return ;
}

void __attribute__ ((weak)) IC1_CallBack(void)
{
    
    // Add your custom callback code here
   ForceCommutation();
   do
    tic1=IC1BUF;    
   while(IC1CON1bits.ICBNE);
    ec.ComutPh1= true;
    if(ec.Current_Direction==CW)
             startcycles++;
        else
             startcycles--;                

}

void __attribute__ ((weak)) IC2_CallBack(void)
{
    // Add your custom callback code here
   ForceCommutation();
   do
        tic2=IC2BUF;    
   while(IC2CON1bits.ICBNE);
   ec.ComutPh2= true;
   if(ec.Current_Direction==CW)
             startcycles++;
        else
             startcycles--;                

}

void __attribute__ ((weak)) IC3_CallBack(void)
{
    // Add your custom callback code here
       ForceCommutation();
       t1.hl= t2.hl;      
       t2.l=IC3BUF;
       while(IC3CON1bits.ICBNE)
        tax3=IC3BUF;    
       t2.h=IC4BUF;    
       while(IC4CON1bits.ICBNE)
        tay3=IC4BUF;         
       ec.ComutPh3= true;
       if(ec.Current_Direction==CW)
             startcycles++;
        else
             startcycles--;    
        dt.hl= t2.hl-t1.hl;//time between Hall sensor detections 
        if(ec.Last_Direction == ec.Current_Direction)
        {
            if(dt.hl < THMIN)
                err.Interfer= true;
        }       
        ec.Last_Direction=ec.Current_Direction;
       
}

void pwmvolt(int permilleratio)     //set ratio of pwm output; max. ratio is +/- 1000 of 1024  
{
   uint32_t lotr;
   if(permilleratio==0)
       MDC= PTPER>>1;       //0.5 duty cycle
   else
   {
     if(permilleratio < 0)
     {
      permilleratio = -permilleratio;
      ec.Required_Direction= CCW;
     }
     else
      ec.Required_Direction= CW;
     if(permilleratio > 1000)permilleratio = 1000;
     lotr= ((uint32_t)(permilleratio + 0x400)) * PTPER;//t
     MDC= lotr >> 11; 
   }
}

bool ramp(int16_t *ptvelo, int16_t endvelo,int16_t updown)//on slopes(pointer to actual value, final value, absolute slope)
{
    bool G= true;
    if(updown<0)updown= -updown;
    if((endvelo> *ptvelo))
    {        
      *ptvelo += updown;
      if(*ptvelo > endvelo)
          *ptvelo= endvelo;
    }
    else if((endvelo < *ptvelo))
    {
          *ptvelo -= updown;
         if(*ptvelo < endvelo)
            *ptvelo= endvelo;
    }
    else G= false;
    return G;

}

