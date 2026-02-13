# ECdrive24V  

BRAKE: BLDC motor drive of 12kN brake(MPLABX, XC16, Intel.hex).    
 &emsp;   Main.c: Reset and main cycle.    
 &emsp;   Control.c: Control program for this application.  
&emsp;Variousfcs.c: Auxiliary functions.   
&emsp;  Ecmotor.c: Motor commutation according to Hall sensors.  
&emsp;  Modbus.c: Some basic modbus protocol functions.  
&emsp;  Crc.c: Generate Modbus control word.  
 &emsp; Sericom.c : Uart for Modbus.    
SIGNAL BRAKE: firmware of optional signalizing card, communicates by Modbus(MPLABX, XC8, Intel.hex).   
BOOTLOAD: Optional uart bootloader(MPLABX, XC16, Intel.hex)  
WINBRAKE: Windows monitor program, communicates by Modbus (Visual Studio, C#, WinBrake.exe in Release.zip).  
&emsp;More at https://emar.cz
