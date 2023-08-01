#ifndef __HDCP_H__
#define __HDCP_H__



#ifdef DEMO_HDCP_KEY
	#define NUM_HDCP_KSV    	8		//5 bytes + 0x00 0x00 0x00
	//demo key NUM_HDCP_KSV=8, NovatekHDCP_Writer=5, TPV_Writer=8
	#define NUM_HDCP_KEY    	287		//280+2(0x68+op)+5(factory id)
	#define NUM_HDCP_TOTAL	(NUM_HDCP_KEY+NUM_HDCP_KSV)
	//#define DEMO_HDCP_KEY
#else
	#define NUM_HDCP_KSV    5
	#define NUM_HDCP_KEY    284
	#define NUM_HDCP_TOTAL  (NUM_HDCP_KEY+NUM_HDCP_KSV)
#endif
#define OP_CODE	0x68

// Macro Function
#define EnableHDCP()  WriteIIC560(0x360, 0x40); \
                      WriteIIC560(0x368, 0x74); \
                      WriteIIC560(0x369, 0x0B);
#define DisableHDCP() WriteIIC560(0x369, 0x03);

//
void InitHDCP(void);
void WriteHDCPKey(void);
void CheckHDCP(void);
void CheckHDCPSyncMode(void);

#ifdef NOVATEK_HDCP_WRITER
void StartHDCPStoring(void);
void StoreHDCP( unsigned char *pData,  unsigned short num);
unsigned char CheckHDCPChkSum(void);
#endif

#ifdef DEMO_HDCP_KEY
void InitHDCP_DemoKey();
#endif

extern xdata unsigned char ucHDCPFlag;
extern xdata unsigned short usNVRamAddr_HDCP;
extern xdata unsigned short usHDCPChkSum1, usHDCPChkSum2;

#endif