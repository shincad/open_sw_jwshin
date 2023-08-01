/***********************************************************************/
/*             Novatek MicroElectronics Corp.                          */
/*    2F, No. 3,Innovation Road 1, Science-Based Industrial Park,      */
/*    HsinChu 300,Taiwn, R.O.C.                                        */
/*    TEL:886-3-567-0889       FAX:886-3-577-0132                      */
/*    All Rights Reserved                                              */
/***********************************************************************/
/***********************************************************************/
/*    fe2p_lib.h                                                       */
/*    Release Date:2006/10/24      Last Maintenance:2006/10/30         */
/*    Original Version:1.0.00      Last Version:1.0.00                 */
/*    Coding By:Alvin Lin          Maintenance By:Alvin Lin            */
/***********************************************************************/
#ifndef _FE2P_LIB_H
#define _FE2P_LIB_H

extern void Fe2p_WriteEnable(void);
extern void Fe2p_WriteStatus(unsigned char Data);
extern void Fe2p_SectorErase(unsigned short Sector);
extern void Fe2p_ByteWrite(unsigned short Ptr,unsigned char Data);
extern void Fe2p_PageWrite(unsigned short Faddr,unsigned short Saddr,unsigned char Length);
extern void Fe2p_ByteRead(unsigned short Ptr,unsigned char *Data);
extern void Fe2p_PageRead(unsigned short Ptr,unsigned char *Data,unsigned short Length);

#endif