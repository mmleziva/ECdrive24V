#ifndef ECMOTOR_H
#define	ECMOTOR_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdbool.h>
#include <libq.h>
//#include "mcc_generated_files/ic1.h"

//#define INV  //if Hall sensors have inverse logic

 #define CCW    	1		// Counter Clock Wise direction
 #define CW      0		// Clock Wise direction
#define THMIN 6000

typedef union       //16 single bits amd uint16_t union
{ 
    unsigned int i;
    struct 
    {
	 unsigned int b0: 1;   
	 unsigned int b1: 1;
     unsigned int b2: 1;
     unsigned int b3: 1;   
	 unsigned int b4: 1;
     unsigned int b5: 1;
     unsigned int b6: 1;   
	 unsigned int b7: 1;
     unsigned int b8: 1;
     unsigned int b9: 1;   
	 unsigned int b10: 1;
     unsigned int b11: 1;
     unsigned int b12: 1;
     unsigned int b13: 1;   
	 unsigned int b14: 1;
     unsigned int b15: 1;
    }; 
    struct
    {
     uint8_t L;  
     uint8_t H;
    };
} bint;

typedef union
{ 
    int32_t il;
    uint32_t hl;
    struct 
    {
	 uint16_t l;
     uint16_t h;	 
    }; 
    struct 
    {
	 int16_t j;
     int16_t i;	 
    }; 
    _Q16 q;
    float f;
} unil;

typedef struct 
{
   uint16_t Required_Direction:1;
   uint16_t Current_Direction:1;
   uint16_t Actual_Direction:1;
   uint16_t Last_Direction:1;
   uint16_t Orient:1;
   uint16_t ComutPh1:1;// flag of hall sensor detection of communication
   uint16_t ComutPh2:1;
   uint16_t ComutPh3:1;
   uint16_t SlowToBrake:1;
   uint16_t Run:1;
   uint16_t INV:1;
   uint16_t Left:1;
   uint16_t Quick:1;
   uint16_t Tcapt:1;
} motorbits;

typedef union
{
    struct
    {
        uint16_t Halls:1;
        uint16_t Interfer:1;
        uint16_t Winding:1;
        uint16_t :1;
        uint16_t WatchDog:1;
        uint16_t :1;
        uint16_t WeakPower:1;
        uint16_t LowPower:1;
        uint16_t LowPressure:1;
        uint16_t SlowPress:1;
        uint16_t Opening:1;
        uint16_t :1;
        uint16_t State:4;   
    };
    uint16_t W;
    
   
} errors;


extern int state;
extern int16_t startcycles;
extern motorbits ec;
extern unil t1,t2,dt;
extern errors err;
//void  IC1_CallBack(void);
//void  IC2_CallBack(void);
//void  IC3_CallBack(void);
void  ForceCommutation(void);
void IC1nucleo(void);
void IC2nucleo(void);
void IC3nucleo(void);
void pwmvolt(int permilleratio);
int ramp(int16_t velo, int16_t endvelo,int16_t updown);
#endif	/* ECMOTOR */

