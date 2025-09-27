#include "sericom.h"

char sync;
char rxData,rstring[BUFINMAX+1];
short int irx,nstr;
UARTFLAGS uarf1, uarf2;
bool FURT;
//bool DE;
unsigned char  *pbufo;
uint16_t  BufDMA[BUFOUTMAX],axbuf, timwuart;

void serini()
{
     RPINR18bits.U1RXR = 0x0013;    //RA3->UART1:U1RX
     RPOR1bits.RP36R = 0x0001;    //RB4->UART1:U1TX
     
    //    UTXI: UART1 Transmitter
    //    Priority: 3
        IPC3bits.U1TXIP = 3;//test //1;
    //    URXI: UART1 Receiver
    //    Priority: 2
        IPC2bits.U1RXIP = 2;
    pbufo=(unsigned char *)(&BufDMA[0]);
 //uart harmony interrupt handlers   
  
  uarf1.Fred= true;//t
  axbuf= __builtin_dmaoffset(&BufDMA[0]);
  DMA_StartAddressASet(DMA_CHANNEL_0,axbuf);
  U1BRG = BRGVAL;
  U1MODEbits.UARTEN=true;
  IEC0bits.U1RXIE = true; 
  DMA0PAD = (volatile unsigned int) &U1TXREG;
  //U1STAbits.UTXEN= true;
  U1MODEbits.BRGH=true;
}

void __attribute__ ((weak)) DMA_Channel0_CallBack(void)
{
    // Add your custom callback code here
   uarf1.WRITBUSY=false; 
   while(!U1STAbits.TRMT);
   U1STAbits.UTXEN= false;
   DMA_ChannelDisable(DMA_CHANNEL_0);//t
   timwuart=0;
   DE= false;
   
}


//receive data ISR
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt (void)
{
  if(!T4CONbits.TON)
  {
   uarf1.ErrPar=0;
   TMR4_Start();
   irx=0;
  }
  TMR4 = 0;			  
  _T4IF=0;
  while(_U1RXIF)
  {
    _U1RXIF=0;//t
    rxData=(char)U1RXREG;
     if(irx < BUFINMAX)
     {
      rstring[irx]= rxData;    
      irx++;//number of chars received 
     }
  }
  if(U1STAbits.OERR)
  {
      U1STAbits.OERR=0;	
  }
  return;
}

void startU1tr(int n)//start transmit of this card data to UART1->USB 
{
// if(!uarf1.WRITBUSY)//t
 {
     uarf1.WRITBUSY= true;
     DE= true;
     DMA0CNT= n;
     DMA_ChannelEnable(DMA_CHANNEL_0);
     U1STAbits.UTXEN= true;
     DMA_SoftwareTriggerEnable(DMA_CHANNEL_0);
 }
} 

inline void restartuart()
{
     U1MODEbits.UARTEN=false;
     DMA_Channel0_CallBack();
     serini();
}