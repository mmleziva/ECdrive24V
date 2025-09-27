#include "modbus.h"

 uint16_t ADR0COILS;    
 uint16_t ADR0DISCIN; 
 uint16_t ADR0INPREG=30000; 
 uint16_t ADR0HOLDREG=40000; 

UARTFLAGS mbu;//*puf;
//short int N;
unsigned int N;
//short int numrec;
unsigned int numrec;
SHORT aux;
//short int shaddr;
//uint8_t shaddr;
uint16_t shaddr;
unsigned char *pbi, *pbo, byten;
short  int Regs;

WORD HOLDREGS[NREGS];
WORD INPREGS[INREGS];

MODBUSTRUCT mbs, mbm;  //modbus structures
 

void TMR2_ISR(void)
{
    TMR2IF= false;
    if(irx >3)
    {
     T2CONbits.T2ON= false;
  //   mbu.ErrPar= uarf1.ErrPar; 
     mbu.Rec= 1;
     //mbu.Uart1=1;
     pbi= (unsigned char *) rstring;
     numrec= irx;
    }
    irx=0;
}

unsigned char * mbrcopy(unsigned char *p, WORD *q, unsigned int n )//read n words from char array pointered by p to word array pointered by q 
{
    unsigned int i=n;
    while(i> 0)
    {
     q->H = *p;
     p++;
     q->L = *p;
     p++;
     q++;
     i--;
    }
    return p;
}

unsigned char * mbwcopy(WORD *q, unsigned char *p,  unsigned int n )//write n words from word array pointered by q to char array pointered by p 
{
    unsigned int i=n;
    while(i> 0)
    {
     *p= q->H;
     p++;
     *p= q->L;
     p++;
     q++;
     i--;
    }
    N += n;
    N += n;
    return p;
}

//modbus master read
void mbmr()
{
  mbm.errcode=0;
  mbm.CRC= CRC16( pbi, numrec );
  if((mbm.CRC !=0) || mbu.ErrPar )
      mbm.errcode=3; //ILLEGAL DATA
  mbm.unitId= *pbi;
  pbi++;
  mbm.funCode= *pbi;
  pbi++;
  switch(mbm.funCode) 
  {
      case 0x03:                
        mbm.byteCount=  *pbi; 
        pbi++;
        shaddr= (mbm.startAdr.W - ADR0HOLDREG);
        pbi= mbrcopy(pbi, &HOLDREGS[shaddr],mbm.regCount.W);          
      break;
       case 0x04:                
        mbm.byteCount=  *pbi; 
        pbi++;
        shaddr= (mbm.startAdr.W - ADR0INPREG);
        pbi= mbrcopy(pbi, &INPREGS[shaddr],mbm.regCount.W);          
      break;
      case 0x10:
         mbm.startAdr.H= *pbi; 
         pbi++;
         mbm.startAdr.L= *pbi;
         pbi++;
         mbm.regCount.H= *pbi;
         pbi++;
         mbm.regCount.L= *pbi;    
       default:
         mbm.errcode=1;
      
      break;
  }
  
}
//modbus master write

void mbmw(unsigned char UnitAddr, unsigned char Func, unsigned int Faddr, unsigned int Regs)
{
  pbo=pbufo;
//  pbo=tstring;
  N=0;
  mbm.errcode=0;
  mbm.unitId=UnitAddr;
  mbm.funCode= Func;
  *pbo= mbm.unitId;
  pbo++; N++;
  *pbo=mbm.funCode; 
  pbo++; N++;
  switch(mbm.funCode) 
  {
      case 0x03:            
         mbm.startAdr.W= Faddr;
         mbm.regCount.W = Regs;         
         *pbo=mbm.startAdr.H; 
         pbo++;N++;
         *pbo=mbm.startAdr.L;
         pbo++;N++;
         *pbo=mbm.regCount.H;
         pbo++;N++;
         *pbo=mbm.regCount.L; 
         pbo++;N++;     
      break;
        case 0x04:            
         mbm.startAdr.W= Faddr;
         mbm.regCount.W = Regs;         
         *pbo=mbm.startAdr.H; 
         pbo++;N++;
         *pbo=mbm.startAdr.L;
         pbo++;N++;
         *pbo=mbm.regCount.H;
         pbo++;N++;
         *pbo=mbm.regCount.L; 
         pbo++;N++;     
      break;
      case 0x10:
      {
         mbm.startAdr.W= Faddr;
         mbm.regCount.W = Regs;         
         *pbo=mbm.startAdr.H; 
         pbo++;N++;
         *pbo=mbm.startAdr.L;
         pbo++;N++;
         *pbo=mbm.regCount.H;
         pbo++;N++;
         *pbo=mbm.regCount.L;
         pbo++;N++;         
         mbm.byteCount = (uint8_t)(Regs <<1) ;
         *pbo=mbm.byteCount;
         pbo++; N++;
         shaddr= (mbm.startAdr.W - ADR0HOLDREG);
         unsigned int Regs= mbm.regCount.W;
         pbo= mbwcopy(&HOLDREGS[shaddr],pbo, Regs);
   //      N+= (Regs <<1);//t
      }
      break;
      default:
          mbm.errcode=1;
  }
 aux.UI= CRC16(pbufo, N);  
 // aux.UI= CRC16(tstring, N);  
  *pbo=aux.UB[0];
  pbo++; N++;
  *pbo= aux.UB[1];
  //if(mbu.Uart1)
      startU1tr(N+1);

}


void mbsr() //modbus slave read
{
  mbs.errcode=0;
  //mbu.ErrPar =0;
  mbs.CRC= CRC16( pbi, numrec );
 // if((mbs.CRC !=0)|| mbu.ErrPar)
  if(mbs.CRC ==0)//t
 //     mbs.errcode= -1;   //ILLEGAL DATA
  //else
  {
   mbs.unitId= *pbi;
   pbi++;
   mbs.funCode= *pbi;
   pbi++; 
   switch(mbs.funCode) 
   {
      case 0x03:                                 
         mbs.startAdr.H= *pbi; 
         pbi++;
         mbs.startAdr.L= *pbi;
         pbi++;
         mbs.regCount.H= *pbi;
         pbi++;
         mbs.regCount.L= *pbi;     
         pbi++;
         mbs.received= true;
      break;
      case 0x04:                                 
         mbs.startAdr.H= *pbi; 
         pbi++;
         mbs.startAdr.L= *pbi;
         pbi++;
         mbs.regCount.H= *pbi;
         pbi++;
         mbs.regCount.L= *pbi;     
         pbi++;
         mbs.received= true;
      break;
      case 0x10:
         mbs.startAdr.H= *pbi; 
         pbi++;
         mbs.startAdr.L= *pbi;
         pbi++;
         mbs.regCount.H= *pbi;
         pbi++;
         mbs.regCount.L= *pbi;  
         pbi++;
         mbs.byteCount= *pbi;
         pbi++;
         shaddr= (mbs.startAdr.W - ADR0HOLDREG);
         if(((int)shaddr < 0)||((shaddr + mbs.regCount.W)> NREGS))
                 mbs.errcode= 2;
         else
         mbrcopy(pbi, &HOLDREGS[shaddr],mbs.regCount.W);  
         mbs.received= true;
      break;
      default:
          mbs.errcode=1;
   }       
  }  
}

//modbus slave write
void mbsw() //modbus slave write
{
  pbo=pbufo;
  //  pbo=tstring;
  N=0;
  *pbo=mbs.unitId;
  pbo++;N++;
   if(mbs.errcode != 0)
   {
       *pbo=mbs.funCode +0x80;
       pbo++; N++;
       *pbo=mbs.errcode; 
       pbo++; N++;
   }     
   else
   {
    *pbo=mbs.funCode; 
    pbo++; N++;
    switch(mbs.funCode) 
    {
      case 0x03:                     
        mbs.byteCount=(uint8_t)(mbs.regCount.W << 1);      
        *pbo=mbs.byteCount; 
        pbo++; N++;
        shaddr= (mbs.startAdr.W - ADR0HOLDREG);
         unsigned int Regs= mbs.regCount.W;
         pbo= mbwcopy(&HOLDREGS[shaddr],pbo,Regs);      
      break;
      case 0x04:                     
        mbs.byteCount= (uint8_t)(mbs.regCount.W << 1);      
        *pbo=mbs.byteCount; 
        pbo++; N++;
        shaddr= (mbs.startAdr.W - ADR0INPREG);
        Regs= mbs.regCount.W;
         pbo= mbwcopy(&INPREGS[shaddr],pbo,Regs);      
      break;
      case 0x10:              
         *pbo=mbs.startAdr.H; 
         pbo++; N++;
         *pbo=mbs.startAdr.L;
         pbo++; N++;
         *pbo=mbs.regCount.H;
         pbo++; N++;
         *pbo=mbs.regCount.L;
         pbo++; N++;        
      break;
      default:
          mbs.errcode=1;
    }
  }
  aux.UI= CRC16(pbufo, N);
  //aux.UI= CRC16(tstring, N);
  *pbo=aux.UB[0];
  pbo++; N++;
  *pbo= aux.UB[1];
  mbs.readysend = true;
 #ifdef MBUART1
  if(mbu.Uart1)   
  {
    startU1tr(N);//start transmit of this card data to UART1->USB 
 
  }
#endif
  #ifdef MBUART2
  if(mbu.Uart2)
      //startU2tr(N);
#endif
}

/*
void modrec(void)
{
    if(mbu.Rec)
    {
        mbu.Rec=0;
        {
            mbu.Master=0;
            mbsr(); 
            if(mbs.CRC==0)
            {
             interf();
             mbsw();
//             mwend();
            }
        }
    
    }
}
*/

