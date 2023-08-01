rem Master Link Batch File............
lnk68k -o %1.abs -c d:\mcc68k\expmst\mcc68k.cmd
hexbin2 <%1.dat
v %1
