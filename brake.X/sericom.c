#include "sericom.h"
char sync;
char rxData,rstring[BUFINMAX+1];
short int irx,nstr;
UARTFLAGS uarf1, uarf2;
bool FURT;
bool DE;
//unsigned char bufout[BUFOUTMAX+1],bufin[BUFINMAX+1];
//unsigned char bufin[BUFINMAX+1];
unsigned char  *pbufo;
uint16_t  BufDMA[BUFOUTMAX],axbuf;

void serini()
{
     RPINR18bits.U1RXR = 0x0013;    //RA3->UART1:U1RX
     RPOR1bits.RP36R = 0x0001;    //RB4->UART1:U1TX
     
    //    UTXI: UART1 Transmitter
    //    Priority: 1
        IPC3bits.U1TXIP = 1;
    //    URXI: UART1 Receiver
    //    Priority: 1
        IPC2bits.U1RXIP = 1;
 //pbufo=&bufout[0];'
    pbufo=(unsigned char *)(&BufDMA[0]);
 //uart harmony interrupt handlers   
  
  uarf1.Fred= true;//t
  axbuf= __builtin_dmaoffset(&BufDMA[0]);
  DMA_StartAddressASet(DMA_CHANNEL_0,axbuf);
  U1BRG = BRGVAL;
//  U1BRG = 0x83;//t
  U1MODEbits.UARTEN=true;
  IEC0bits.U1RXIE = true; 
  DMA0PAD = (volatile unsigned int) &U1TXREG;
  U1STAbits.UTXISEL0= true;//t
  U1STAbits.UTXEN= true;
 //  _U1RXIF=0;
  U1MODEbits.BRGH=true;
  // U1MODEbits.UARTEN=true;
 //  IEC0bits.U1TXIE= true;
}

void __attribute__ ((weak)) DMA_Channel0_CallBack(void)
{
    // Add your custom callback code here
   uarf1.WRITBUSY=false; 
   while(!U1STAbits.TRMT);
   DE= false;
   
}


//receive data ISR
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt (void)
/*  
 if(!uarf1.Fred)
 {
     bci=(char)U1RXREG;  
     {   
      U1TXREG= sync=0xaa;//t
     }
 }
 else
 */ 
 {
  if(!T4CONbits.TON)
  {
   uarf1.ErrPar=0;
   TMR4_Start();
   irx=0;
  }
  TMR4 = 0;			  
  _T4IF=0;
  if(U1STAbits.OERR)U1STAbits.OERR=0;		// Enable UART Tx 
  rxData=(char)U1RXREG;
  if(irx < BUFINMAX)
  {
   rstring[irx]= rxData;    
   irx++;//number of chars received 
  }
 // else
 //     rxData=0x55;//t
 _U1RXIF=0;//t
 return;
}

void startU1tr(int n)//start transmit of this card data to UART1->USB 
{
 if(!uarf1.WRITBUSY)
 {
     uarf1.WRITBUSY= true;
     DE= true;
     DMA0CNT= n;
     DMA_ChannelEnable(DMA_CHANNEL_0);
  //   _U1TXIF=1;//t
     DMA_SoftwareTriggerEnable(DMA_CHANNEL_0);
 }
} 