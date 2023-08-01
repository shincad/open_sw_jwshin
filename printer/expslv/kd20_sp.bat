mcc68k -c -nKc -Og -Ot main.c
mcc68k -c -nKc -Og -Ot callmst.c
mcc68k -c -nKc -Og -Ot eeprom.c
mcc68k -c -nKc -Og -Ot display.c
mcc68k -c -nKc -Og -Ot panel.c
mcc68k -c -nKc delay.c
link slave
