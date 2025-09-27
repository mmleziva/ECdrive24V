/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F15225
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SW2 aliases
#define SW2_TRIS                 TRISAbits.TRISA0
#define SW2_LAT                  LATAbits.LATA0
#define SW2_PORT                 PORTAbits.RA0
#define SW2_WPU                  WPUAbits.WPUA0
#define SW2_OD                   ODCONAbits.ODCA0
#define SW2_ANS                  ANSELAbits.ANSA0
#define SW2_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define SW2_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define SW2_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define SW2_GetValue()           PORTAbits.RA0
#define SW2_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define SW2_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define SW2_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define SW2_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define SW2_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define SW2_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define SW2_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define SW2_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set SW3 aliases
#define SW3_TRIS                 TRISAbits.TRISA1
#define SW3_LAT                  LATAbits.LATA1
#define SW3_PORT                 PORTAbits.RA1
#define SW3_WPU                  WPUAbits.WPUA1
#define SW3_OD                   ODCONAbits.ODCA1
#define SW3_ANS                  ANSELAbits.ANSA1
#define SW3_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define SW3_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define SW3_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define SW3_GetValue()           PORTAbits.RA1
#define SW3_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define SW3_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define SW3_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define SW3_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define SW3_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define SW3_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define SW3_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define SW3_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set OPEN_G aliases
#define OPEN_G_TRIS                 TRISAbits.TRISA2
#define OPEN_G_LAT                  LATAbits.LATA2
#define OPEN_G_PORT                 PORTAbits.RA2
#define OPEN_G_WPU                  WPUAbits.WPUA2
#define OPEN_G_OD                   ODCONAbits.ODCA2
#define OPEN_G_ANS                  ANSELAbits.ANSA2
#define OPEN_G_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define OPEN_G_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define OPEN_G_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define OPEN_G_GetValue()           PORTAbits.RA2
#define OPEN_G_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define OPEN_G_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define OPEN_G_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define OPEN_G_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define OPEN_G_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define OPEN_G_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define OPEN_G_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define OPEN_G_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set SWT aliases
#define SWT_TRIS                 TRISAbits.TRISA4
#define SWT_LAT                  LATAbits.LATA4
#define SWT_PORT                 PORTAbits.RA4
#define SWT_WPU                  WPUAbits.WPUA4
#define SWT_OD                   ODCONAbits.ODCA4
#define SWT_ANS                  ANSELAbits.ANSA4
#define SWT_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SWT_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SWT_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SWT_GetValue()           PORTAbits.RA4
#define SWT_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SWT_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define SWT_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define SWT_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define SWT_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define SWT_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define SWT_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define SWT_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set IO_RA5 aliases
#define IO_RA5_TRIS                 TRISAbits.TRISA5
#define IO_RA5_LAT                  LATAbits.LATA5
#define IO_RA5_PORT                 PORTAbits.RA5
#define IO_RA5_WPU                  WPUAbits.WPUA5
#define IO_RA5_OD                   ODCONAbits.ODCA5
#define IO_RA5_ANS                  ANSELAbits.ANSA5
#define IO_RA5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define IO_RA5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define IO_RA5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define IO_RA5_GetValue()           PORTAbits.RA5
#define IO_RA5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define IO_RA5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define IO_RA5_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define IO_RA5_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define IO_RA5_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define IO_RA5_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define IO_RA5_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define IO_RA5_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set CLOS_Y aliases
#define CLOS_Y_TRIS                 TRISCbits.TRISC0
#define CLOS_Y_LAT                  LATCbits.LATC0
#define CLOS_Y_PORT                 PORTCbits.RC0
#define CLOS_Y_WPU                  WPUCbits.WPUC0
#define CLOS_Y_OD                   ODCONCbits.ODCC0
#define CLOS_Y_ANS                  ANSELCbits.ANSC0
#define CLOS_Y_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define CLOS_Y_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define CLOS_Y_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define CLOS_Y_GetValue()           PORTCbits.RC0
#define CLOS_Y_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define CLOS_Y_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define CLOS_Y_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define CLOS_Y_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define CLOS_Y_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define CLOS_Y_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define CLOS_Y_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define CLOS_Y_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set RUN_B aliases
#define RUN_B_TRIS                 TRISCbits.TRISC1
#define RUN_B_LAT                  LATCbits.LATC1
#define RUN_B_PORT                 PORTCbits.RC1
#define RUN_B_WPU                  WPUCbits.WPUC1
#define RUN_B_OD                   ODCONCbits.ODCC1
#define RUN_B_ANS                  ANSELCbits.ANSC1
#define RUN_B_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RUN_B_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RUN_B_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RUN_B_GetValue()           PORTCbits.RC1
#define RUN_B_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RUN_B_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RUN_B_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define RUN_B_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define RUN_B_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define RUN_B_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define RUN_B_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define RUN_B_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set ERR_R aliases
#define ERR_R_TRIS                 TRISCbits.TRISC2
#define ERR_R_LAT                  LATCbits.LATC2
#define ERR_R_PORT                 PORTCbits.RC2
#define ERR_R_WPU                  WPUCbits.WPUC2
#define ERR_R_OD                   ODCONCbits.ODCC2
#define ERR_R_ANS                  ANSELCbits.ANSC2
#define ERR_R_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define ERR_R_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define ERR_R_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define ERR_R_GetValue()           PORTCbits.RC2
#define ERR_R_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define ERR_R_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define ERR_R_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define ERR_R_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define ERR_R_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define ERR_R_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define ERR_R_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define ERR_R_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set R aliases
#define R_TRIS                 TRISCbits.TRISC3
#define R_LAT                  LATCbits.LATC3
#define R_PORT                 PORTCbits.RC3
#define R_WPU                  WPUCbits.WPUC3
#define R_OD                   ODCONCbits.ODCC3
#define R_ANS                  ANSELCbits.ANSC3
#define R_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define R_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define R_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define R_GetValue()           PORTCbits.RC3
#define R_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define R_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define R_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define R_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define R_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define R_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define R_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define R_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set DE_RE aliases
#define DE_RE_TRIS                 TRISCbits.TRISC4
#define DE_RE_LAT                  LATCbits.LATC4
#define DE_RE_PORT                 PORTCbits.RC4
#define DE_RE_WPU                  WPUCbits.WPUC4
#define DE_RE_OD                   ODCONCbits.ODCC4
#define DE_RE_ANS                  ANSELCbits.ANSC4
#define DE_RE_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define DE_RE_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define DE_RE_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define DE_RE_GetValue()           PORTCbits.RC4
#define DE_RE_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define DE_RE_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define DE_RE_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define DE_RE_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define DE_RE_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define DE_RE_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define DE_RE_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define DE_RE_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set D aliases
#define D_TRIS                 TRISCbits.TRISC5
#define D_LAT                  LATCbits.LATC5
#define D_PORT                 PORTCbits.RC5
#define D_WPU                  WPUCbits.WPUC5
#define D_OD                   ODCONCbits.ODCC5
#define D_ANS                  ANSELCbits.ANSC5
#define D_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define D_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define D_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define D_GetValue()           PORTCbits.RC5
#define D_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define D_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define D_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define D_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define D_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define D_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define D_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define D_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/