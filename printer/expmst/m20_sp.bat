rem Master Compile Batch file .............
rem Phoenix Information Technology ........
rem Shin Jung Wook....
rem --------------------  Module Compile....
mcc68k -c -nKc -Og -Ot m_main.c
mcc68k -c -nKc sio_int.c
mcc68k -c -nKc sm_int.c
mcc68k -c -nKc sio_init.c
mcc68k -c -nKc -Og -Ot getsio.c
mcc68k -c -nKc -Og -Ot gethost.c
mcc68k -c -nKc -Og -Ot chkhost.c
mcc68k -c -nKc -Og -Ot chksio.c
mcc68k -c -nKc -Og -Ot lfproc.c
mcc68k -c -nKc -Og -Ot send_img.c
mcc68k -c -nKc -Og -Ot adj_err.c
mcc68k -c -nKc -Og -Ot exprol.c
mcc68k -c -nKc -Og -Ot expsbuff.c
mcc68k -c -nKc -Og -Ot expload.c
mcc68k -c -nKc -Og -Ot rolproc.c
mcc68k -c -nKc -Og -Ot sendbuff.c
mcc68k -c -nKc -Og -Ot sb300.c
mcc68k -c -nKc -Og -Ot sb8lpi.c
mcc68k -c -nKc -Og -Ot sendslv.c
mcc68k -c -nKc -Og -Ot clrstimg.c
mcc68k -c -nKc -Og -Ot tostimg.c
mcc68k -c -nKc -Og -Ot copyimg.c
mcc68k -c -nKc -Og -Ot loadtb.c
mcc68k -c -nKc -Og -Ot htdbtb.c
mcc68k -c -nKc -Og -Ot vtdbtb.c
mcc68k -c -nKc -Og -Ot htcdtb.c
mcc68k -c -nKc -Og -Ot htvtdbtb.c
mcc68k -c -nKc -Og -Ot han11f.c
mcc68k -c -nKc -Og -Ot rvmem.c
mcc68k -c -nKc -Og -Ot sdmem.c
mcc68k -c -nKc -Og -Ot ulmem.c
mcc68k -c -nKc -Og -Ot bfmem.c
mcc68k -c -nKc -Og -Ot makekor.c
mcc68k -c -nKc -Og -Ot makeeng.c
mcc68k -c -nKc -Og -Ot emul.c
mcc68k -c -nKc -Og -Ot cjt.c
mcc68k -c -nKc -Og -Ot ctrproc.c
mcc68k -c -nKc -Og -Ot escproc.c
mcc68k -c -nKc -Og -Ot ctrkssm.c
mcc68k -c -nKc -Og -Ot esckssm.c
mcc68k -c -nKc -Og -Ot fsproc.c
mcc68k -c -nKc -Og -Ot ctrtg.c
mcc68k -c -nKc -Og -Ot esctg.c
mcc68k -c -nKc -Og -Ot autoclr.c
mcc68k -c -nKc -Og -Ot selftest.c
mcc68k -c -nKc -Og -Ot institem.c
mcc68k -c -nKc m_init.c
mcc68k -c -nKc saveatt.c
mcc68k -c -nKc setatt.c
mcc68k -c -nKc loadatt.c
mcc68k -c -nKc selfslv.c
mcc68k -c -nKc -Og -Ot getpio.c
mcc68k -c -nKc -Og -Ot chkpio.c
mcc68k -c -nKc -Og -Ot conprn.c
rem -------------- Link and Split and Shuff....
link master
