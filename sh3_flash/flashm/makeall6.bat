rem 環境に合わせて各実行ファイルやライブラリのパスの設定を行なってください

echo OFF
echo input=boot.obj                         >  flash2.sub
echo input=vector.obj                       >> flash2.sub
echo input=inter.obj                        >> flash2.sub
echo input=main.obj                         >> flash2.sub
echo input=comm.obj                         >> flash2.sub
echo input=sci.obj                          >> flash2.sub
echo input=29fxxx.obj                       >> flash2.sub
echo input=int_asm.obj                      >> flash2.sub
echo library %shc_lib%\..\lib\shc3npb.lib   >> flash2.sub
echo output=flash2.mot                      >> flash2.sub
echo list=flash2.map                        >> flash2.sub
echo show=symbol                            >> flash2.sub
echo rom=D=R                                >> flash2.sub
echo start=start/00000000                   >> flash2.sub
echo start=int100/00000100                  >> flash2.sub
echo start=int400/00000400                  >> flash2.sub
echo start=int600,P,C,D/00000600            >> flash2.sub
echo start=R,B/010000000                    >> flash2.sub
echo form=stype                             >> flash2.sub
echo exit                                   >> flash2.sub
echo ON

shc /op=0 /cpu=SH3 /endian=b /define=_SHC3_ /show=ob,noso /list boot.c
shc /op=0 /cpu=SH3 /endian=b /define=_SHC3_ /show=ob,noso /list vector.c
shc /op=0 /cpu=SH3 /endian=b /define=_SHC3_ /show=ob,noso /list inter.c
shc /op=0 /cpu=SH3 /endian=b /define=_SHC3_ /show=ob,noso /list main.c
shc /op=0 /cpu=SH3 /endian=b /define=_SHC3_ /show=ob,noso /list comm.c
shc /op=0 /cpu=SH3 /endian=b /define=_SHC3_ /show=ob,noso /list sci.c
shc /op=0 /cpu=SH3 /endian=b /define=_SHC3_ /show=ob,noso /list 29fxxx.c

asmsh int_asm.src /cpu=sh3 /object /endian=b /list

optlnk -subcommand=flash2.sub
