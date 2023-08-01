rem Slave Compile Batch File..........
mcc68k  -c -nKc main.c
mcc68k  -c -nKc callmst.i
mcc68k  -c -nKc eeprom.c
mcc68k  -c -nKc display.i
mcc68k  -c -nKc panel.c
mcc68k  -c -nKc delay.i
link slave
