listabs         publics,internals
listmap         publics
;format          ieee
format          s
public          SYS_STACKTOP    = $8FFF0
;public          _heapadd = $8C000
;sectsize        heap=$500
;sectsize        stack=$500
;common          stack=$e0000  ;8fff0
;alignmod        ioports=4
sect            code=$500
sect            vars=$80000

order           code,strings,liternals,const,??INITDATA
order           vars,zerovars,tags,ioports,heap
;order           stack
INITDATA        vars

load startup
load main.obj
load callmst.obj
load eeprom.obj
load display.obj
load delay.obj
load panel.obj
load mcc68kab.lib
end
