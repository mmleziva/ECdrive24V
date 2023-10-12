# ECdrive24V  

BRAKE: BLDC motor drive of 12kN brake.    
  Main.c: Reset and main cycle.    
  Control.c: Control program for this application. 
  Variousfcs.c: Auxiliary functions.  
  Ecmotor.c: Motor commutation according to Hall sensors.  
  Modbus.c: Some basic modbus protocol functions.  
  Crc.c: Generate modbus control word.  
  Sericom.c : Uart for modbus.    
BOOTLOAD: Optional uart bootloader  
WINBRAKE: Windows monitor program, communicates by modbus.
