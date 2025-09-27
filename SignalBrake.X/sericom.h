

#ifndef _SERICOM_H    /* Guard against multiple inclusion */
#define _SERICOM_H
//#define Fosc  121605000
//#define FCY  (Fosc/2)
//#define BAUDRATE 115200
//#define BRGVAL (((FCY/BAUDRATE)/4) - 1)//used by modbus

#define BUFOUTMAX 64 //138
#define BUFINMAX 64  //64
#define DE RC4
#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdbool.h>
#include <stdint.h>

typedef union {
    struct {
        unsigned perr : 1;
        unsigned ferr : 1;
        unsigned oerr : 1;
        unsigned reserved : 5;
    };
    uint8_t status;
}eusart1_status_t;

typedef struct 
{
 unsigned Pre  :1; 
 unsigned Rec  :1; 
 unsigned ErrPar: 1; 
 unsigned Master: 1; 
 unsigned Uart1: 1; 
 unsigned Uart2: 1; 
 unsigned Fred:  1;
 unsigned WRITBUSY: 1;
}UARTFLAGS;

//extern volatile uint8_t eusart1TxBufferRemaining;
//extern volatile uint8_t eusart1RxCount;
//extern void (*EUSART1_RxDefaultInterruptHandler)(void);
void EUSART1_Receive_ISR(void);
void EUSART1_Transmit_ISR(void);
void EUSART1_RxDataHandler(void);

extern bool FURT;
void startU1tr(unsigned int n);
extern UARTFLAGS uarf1, mbu;
extern char rxData;
extern uint8_t rstring[BUFINMAX+1];
extern unsigned short int irx;
extern unsigned char  *pbufo;
void serini();

//#include "config/basic/definitions.h"
#endif /* _SERICOM_H */

