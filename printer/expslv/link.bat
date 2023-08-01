rem Link Batch File....
lnk68k -o %1.abs -c d:\mcc68k\expslv\mcc68k.cmd
hexbin2 <%1.dat
v %1
