To update the program, use one of the methods A, B or C:
A. Connect the PDA pin to 0V directly on the brake board on the programming connector J4, after restarting the controller will remain in bootloader mode.
B. By pressing the button on the signaling board for a long time (at least 2 seconds), restart the brake board in bootloader mode.
C. In the WinBrake monitoring program, enter the number a5a5 in the free field on the right and save it by double-clicking on "Set Params". The board will restart in bootloader mode.

 After restarting, the controller will remain in bootloader mode, the D30 LED will flash quickly. If the brake board is no longer connected to the PC via a USB adapter, reconnect the board while it is running. Run the UnifiedHost program on the PC, select "Device Arch": dsPIC33, "Settings": Serial, correct COM, speed 115200bps, "File": "Open" (find the path to) /brake_for_bootl.hex. Verify and repeat "Read Device Settings" and then run "Program Device".
 Install UnifiedHost from https://github.com/Microchip-MPLAB-Harmony/bootloader/tree/master/tools/UnifiedHost-1.19.3
 Need JavaFX for example from https://www.azul.com/downloads/?version=java-8-lts&package=jdk-fx#zulu or just jre-8u201-windows-x64.exe z https://www.oracle.com/java/technologies/javase/javase8-archive-downloads.html - both require registration
(or they say you can use JDK11+ with OpenJFX).

