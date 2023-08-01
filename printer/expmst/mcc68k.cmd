;               Mcc68k Compiler Command File
;               Kia Information Systems.
;               Printer Development Team.

listabs         publics,internals
listmap         publics
;format          ieee
format          s
public          SYS_STACKTOP    = $10FFF0
;public          _heapadd = $8C000
;sectsize        heap=$500
;sectsize        stack=$500
;common          stack=$e0000  ;8fff0
;alignmod        ioports=4
sect            code=$500
sect            vars=$100000

order           code,strings,liternals,const,??INITDATA
order           vars,zerovars,tags,ioports,heap
;order           stack
INITDATA        vars

load mst
load m_main.obj
load sio_int.obj
load sm_int.obj
load sio_init.obj
load getsio.obj
load gethost.obj
load chkhost.obj
load chksio.obj
load lfproc.obj
load send_img.obj
load adj_err.obj
load exprol.obj
load expsbuff.obj
load expload.obj
load rolproc.obj
load sendbuff.obj
load sb300.obj
load sb8lpi.obj
load sendslv.obj
load clrstimg.obj
load tostimg.obj
load copyimg.obj
load loadtb.obj
load htdbtb.obj
load vtdbtb.obj
load htcdtb.obj
load htvtdbtb.obj
load han11f.obj
load rvmem.obj
load sdmem.obj
load ulmem.obj
load bfmem.obj
load makekor.obj
load makeeng.obj
load emul.obj
load cjt.obj
load ctrproc.obj
load escproc.obj
load ctrkssm.obj
load esckssm.obj
load fsproc.obj
load ctrtg.obj
load esctg.obj
load autoclr.obj
load selftest.obj
load institem.obj
load m_init.obj
load saveatt.obj
load setatt.obj
load loadatt.obj
load selfslv.obj
load getpio.obj
load chkpio.obj
load delay.obj
load conprn.obj
load mcc68kab.lib
end
