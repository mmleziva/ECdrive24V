#include "sericom.h"
uint8_t rstring[BUFINMAX+1], tstring[BUFOUTMAX+1], raux;
//uint8_t  irx;
//uint8_t _eusart1RxCount;
char sync;
//char rxData,rstring[BUFINMAX+1];
unsigned short int irx,tm,itx;
UARTFLAGS uarf1;
bool FURT;

unsigned char  *pbufo;

void EUSART1_RxDataHandler(void){
    TMR2=0;
    if(!T2CONbits.T2ON)
    {
        T2CONbits.T2ON= true;   
    }
  //  TMR2IF= false;
    while(PIR1bits.RC1IF)
    {
        /*
        rstring[irx++] = RC1REG;
        if(sizeof(rstring) <= irx)
        {
            irx = 0;
        }
         */
        if(sizeof(rstring) > irx)            
                rstring[irx++] = RC1REG;
        else
          raux = RC1REG;  
    }
}

void EUSART1_FramingErrorHandler(void){}

void EUSART1_OverrunErrorHandler(void){
    // EUSART1 error - restart

    RC1STAbits.CREN = 0;
    RC1STAbits.CREN = 1;

}

void serini()
{
    // disable interrupts before changing states
    PIE1bits.RC1IE = 0;
    //EUSART1_SetRxInterruptHandler(EUSART1_Receive_ISR);
    // Set the EUSART1 module to the options selected in the user interface.

    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUD1CON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RC1STA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TX1STA = 0x24;
    TX1STAbits.TXEN= false;//t

    // SPBRGL 34; 
    SP1BRGL = 0x22;

    // SPBRGH 0; 
    SP1BRGH = 0x00;


    //eusart1RxLastError.status = 0;


    irx = 0;
    //eusart1RxTail = 0;
//    eusart1RxCount = 0;

    // enable receive interrupt
    PIE1bits.RC1IE = 1;
    PIE1bits.TX1IE = 1;
    
    pbufo=&tstring[0];//&bufout[0];

    uarf1.Fred= true;//t
  
}


void EUSART1_Receive_ISR(void)
{
    

    if(RC1STAbits.FERR){
        EUSART1_FramingErrorHandler();
    }
    {
        EUSART1_RxDataHandler();
    }

    if(RC1STAbits.OERR){
        EUSART1_OverrunErrorHandler();
    }
    
    //} else
    
    
    // or set custom function using EUSART1_SetRxInterruptHandler()
}

void EUSART1_Transmit_ISR(void)
{
    if(itx < tm)
    {
      TX1REG= tstring[itx++];
    }
    else
    {
        while(!TX1STAbits.TRMT)
        {
            
        }
        uarf1.WRITBUSY= false;
        TX1STAbits.TXEN= false;
        DE= false;
    }
}


void startU1tr(unsigned int n)//start transmit of this card data to UART1->USB 
{
 if(!uarf1.WRITBUSY)
 {
     uarf1.WRITBUSY= true;
     DE= true;
     itx=0;
     tm=n;
     PIR1bits.TX1IF = 1;
     TX1STAbits.TXEN= true;
      
 }
} 