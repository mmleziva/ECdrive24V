/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F15225
        Driver Version    :  2.00
*/

//#include "sericom.h"
#include "modbus.h"
#include "mcc_generated_files/mcc.h"

#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)

#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)


#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

#define VOLTON 0
#define READY 1
#define INTO 2
#define HOLD 3
#define RELEASE 4
#define AWAY 5


typedef union
{
    struct
    {
        uint8_t Halls:1;
        uint8_t Interfer:1;
        uint8_t Winding:1;
        uint8_t :1;
        uint8_t WatchDog:1;
        uint8_t :1;
        uint8_t WeakPower:1;
        uint8_t LowPower:1;
    };
    uint8_t B;   
} errL;

typedef union
{
    struct
    {
        uint8_t LowPressure:1;
        uint8_t SlowPress:1;
        uint8_t Opening:1;
        uint8_t :1;
        uint8_t State:4;   
    };
    uint8_t B;   
} errH;
uint8_t half,intf,windif,lowpof,sloprf,openf, sampf; 
errL erlo;
errH erhi, errhold;
bool SAMP, WAITREC, ERRPAST, ERR_PULSE, PAF;
uint8_t n,errtime;
bool MBSWR;
uint8_t butswrt;

const uint8_t bit_count[256] = {
    0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};


    void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(INTCONbits.PEIE == 1)
    {
        if(PIR1bits.TMR2IF == 1)
        {
            TMR2_ISR();
        }
        else
        if(PIE1bits.RC1IE == 1 && PIR1bits.RC1IF == 1)
        {
            EUSART1_Receive_ISR();
        } 
        else
        if(PIE1bits.TX1IE == 1 && PIR1bits.TX1IF == 1)
        {
            EUSART1_Transmit_ISR();
        }
    }      
    else
    {
        //Unhandled Interrupt
    }
}
uint16_t state;

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    RX1PPS = 0x13;   //RC3->EUSART1:RX1;    
    RC5PPS = 0x05;   //RC5->EUSART1:TX1;    
    serini();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    PIE1bits.TMR2IE = false;
    T2CONbits.ON= false;
    T1CONbits.ON= true;
    ERR_R_SetHigh();

    while (1)
    {
        CLRWDT();
        if(TMR1IF)      //100-130ms cycle
        {
          TMR1IF= false;
          sampf <<= 1;          //no receive filter
          if (SAMP) sampf |= 1; //if sample request not to be succesfully received
          if(bit_count[sampf] > 2)
              ERR_R_PORT= true; //error
          SAMP= true;
          n=0;
          WAITREC= false;  
          if(!ERRPAST && ERR_R_PORT)//ERROR RISE EDGE
                 errtime= 10; 
          if(errtime > 0)       //nmin. 1s 
          {
                  errtime--;
                  ERR_PULSE= true; 
          }          
          else 
            ERR_PULSE= false;     //pulse finished
          ERRPAST= ERR_R_PORT;
          MBSWR = false;//t         drive SW reset by modbus acquire deactivate 
          if(SW2_GetValue())        //if switch not pushed
        //  if(SWT_GetValue())        //if switch not pushed
              butswrt = 0;
          else    
          {
              if(butswrt > 20)  //switch pushed > 2,6s
              {
                  MBSWR= true;
                  butswrt=0;
              }
              else
                  butswrt++;
          }
        }
        if(SAMP && (n<3))
        {
          if(!uarf1.WRITBUSY && !WAITREC) //if an sample has been accepted
          {
              //if(SWT_GetValue())
              //if(SW2_GetValue())
              if(!MBSWR)
              {
                mbmw(1, 0x04, ADR0INPREG + 17, 1);    // modbus request to read register
              }
              else
              {                     //SW reset of motor drive by modbus
                  HOLDREGS[11].H=0xa5;
                  HOLDREGS[11].L=0xa5;
                  mbmw(1, 0x10, ADR0HOLDREG + 11, 1);  
              }
              n++;
              WAITREC= true;                        //wait to read of answer
          }
        }
        if(mbu.Rec && !uarf1.WRITBUSY)              //if answer from brake has been accepted
        {
          mbu.Rec= false;
          WAITREC = false;                          //waiting for receiving has finished
          mbmr();  
          if(mbm.errcode == 0)
          {
            MBSWR= false;//t  
            erlo.B = INPREGS[17].L;
            erhi.B = INPREGS[17].H;
            RUN_B_PORT= ((erhi.State == INTO ) || (erhi.State == AWAY ) ||(erhi.State == HOLD ));
            CLOS_Y_PORT= ((erhi.State == HOLD ) || (erhi.State == RELEASE ));
            OPEN_G_PORT= ((erhi.State == READY ));
            PAF = ERR_PULSE ;           //errors filter 
  
            lowpof <<= 1;
            if (erlo.LowPower) lowpof |= 1; 
            if(bit_count[lowpof] > 2)
                 PAF= true; 
            
            openf <<= 1;
            if (erhi.Opening) openf |= 1; 
            if(bit_count[openf] > 2)
                PAF= true; 

            half <<= 1;
            if (erlo.Halls) half |= 1;
            if(bit_count[half] > 2)
                PAF= true; 

            windif <<= 1;
            if (erlo.Winding) windif |= 1;
            if(bit_count[windif] > 2) 
               PAF= true; 

            ERR_R_PORT = PAF ;             
            SAMP= false;        //sample finished
            if((errhold.State == INTO)&&  (erhi.State == RELEASE))
                ERR_R_PORT= true;
            errhold.B = erhi.B;
          }
        }      
    }
}
/**
 End of File
*/