Postup update programu jedním ze způsobů A, B nebo C:
A. Přímo na desce Brake na programovacím konektoru J4 propojit pin PDA s 0V , po  restartu  kontrolér zůstane v režimu bootloader
B. Delším stiskem tlačítka na signalizační desce(aspoň 2s) restartovat desku Brake v režimu bootloaderu.
C. V monitorovacím programu WinBrake vložit číslo a5a5 do volného pole vpravo a uložit ho 2x kliknutím na "Set Params" . Deska se restartuje v režimu bootloaderu

 Po  restartu  kontrolér zůstane v režimu bootloader, LED D30 rychle bliká. Pokud deska Brake již není připojena přes adaptér USB  k PC, za běhu desku přepojit. Na PC spustit program UnifiedHost, vybrat tam "Device Arch": dsPIC33, "Settings": Serial, správný COM, rychlost  115200bps, "File": "Open" (najít cestu k)/brake_for_bootl.hex. Ověřit i opakovaně "Read Device Settings" a pak spustit "Program Device"
 UnifiedHost instalovat z https://github.com/Microchip-MPLAB-Harmony/bootloader/tree/master/tools/UnifiedHost-1.19.3
 Potřebnou JavaFX např. z https://www.azul.com/downloads/?version=java-8-lts&package=jdk-fx#zulu nebo jen jre-8u201-windows-x64.exe z https://www.oracle.com/java/technologies/javase/javase8-archive-downloads.html - u obou třeba registraci
 (příp. je prý možno použít  JDK11+ s OpenJFX).

