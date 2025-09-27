/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  dsPIC33EV32GM002
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v5.50
*/


/**
  Section: Included Files
*/
//#include "mcc_generated_files/system.h"

#include "control.h"
int z;      //t
extern unsigned int  bootloader_flag;

/*
                         Main application
 */



int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
   // BOOT_DEMO_Initialize();
    iniControl();
    T5CON= 0x8030;//t
    PR5= 0xffff;    //t
    while (1)
    {
        // Add your application code
      ClrWdt();
      /*
       if(_T5IF)
      {
        _T5IF=0;
        z++;
      //  _RB2= !_RB2;
        if(z > 40)  
        //if(controls.SWREAL)
        {
            _RB2=0;
            z=0;
            __builtin_disable_interrupts();
            bootloader_flag = 0xa5a5;//t
        //   controls.SWREAL=0;//t
            while(1){
                 bootloader_flag = 0xA5A5;//t   
            };  //wait reset
        }
      //  else if(z>10)
      //      _RB2= !_RB2;
 //     if(bootloader_flag == 0xA5A5)
 //         while (1){};
      }    
       * */
 //  z++;//t
      /*
      if((bootloader_flag == 0xA5A5)&& !DE)
      {
  //        z--;
  //         bootloader_flag = 0;//t
        volatile uint16_t dummy;
        while (U1STAbits.URXDA) {
          dummy = U1RXREG;
          (void)dummy;
        }
    // 1) disable UART
       U1STAbits.UTXEN = 0;     // disable transmitter
       U1MODEbits.UARTEN = 0;   // disable module

    // krátké ?ekání, aby se hardware ustálil
       for (volatile int i=0; i<1000; ++i) { asm("nop"); }

   
    // 3) clear status flags (overrun atd.)
       if (U1STAbits.OERR) U1STAbits.OERR = 0;   // clear overrun
       IFS0bits.U1RXIF = 0;
       IFS0bits.U1TXIF = 0;
       IFS4bits.U1EIF  = 0; // pokud existuje

// Disable DMA module 
       DMA0CONbits.CHEN = 0;
       IFS0bits.DMA0IF = 0;      // clear possible flags
          asm volatile ( "reset ");
      }
       */
  //    bootloader_flag = 0;//t
      Control();
      modrec();  //modbus receiving test   
      if((bootloader_flag == 0xA5A5)&& !DE)
                  asm volatile ( "reset ");
    }
    return 1; 
}
/**
 End of File
*/

