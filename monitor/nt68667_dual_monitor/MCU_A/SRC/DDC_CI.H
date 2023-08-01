#ifndef _DDC_Ci_H_
#define  _DDC_Ci_H_

#define CMDOP_GET_VCP		0x01
#define CMDOP_VCP_RPL		0x02
#define CMDOP_SET_VCP		0x03
#define CMDOP_GET_TIMING	0x07
#define CMDOP_SAVE			0x0c
#define CMDOP_SET_CAP		0xf3
#define CMDOP_FACTORY		0xC0	// Philips Entry Factory Command Code
#define CMDOP_ASSET			0xC3	// Philips Smart Manage Command Code

#define ACCESSBUS_ADDR		0x6e


#define VCPOP_NEW_CTRL		0x02
#define VCPOP_RECALL		0x04
#define VCPOP_RECALL_BC		0x05
#define VCPOP_RECALL_HV_POS	0x06
#define VCPOP_RECALL_COLOR	0x08
#define VCPOP_COLOR_INC		0x0B
#define VCPOP_COLOR_REQ		0x0C
#define VCPOP_CLOCK			0x0E
#define VCPOP_BRIGHT		0x10
#define VCPOP_CONTRAST		0x12
#define VCPOP_SEL_COLOR		0x14
#define VCPOP_RGAIN			0x16
#define VCPOP_GGAIN			0x18
#define VCPOP_BGAIN			0x1A
#define VCPOP_AUTO_SET		0x1E
#define VCPOP_AUTO_COLOR	0x1F
#define VCPOP_H_POS			0x20
#define VCPOP_V_POS			0x30
#define VCPOP_H_PHASE		0x3E
#define VCPOP_INPUT			0x60
#define VCPOP_DDC_DATA		0x63
#define VCPOP_ROFFSET		0x6C
#define VCPOP_GOFFSET		0x6E
#define VCPOP_BOFFSET		0x70
#define VCPOP_H_FREQ		0xAC
#define VCPOP_V_FREQ		0xAE
#define VCPOP_DISP_TYPE		0xB6
#define VCPOP_USE_TIME		0xC0
#define VCPOP_APP_KEY		0xC6
#define VCPOP_CTRL_TYPE		0xC8
#define VCPOP_FW_LEVEL		0xC9
#define VCPOP_OSD_LOCK		0xCA
#define VCPOP_LANGUAGE		0xCC
#define VCPOP_POWER_MODE	0xD6
#define VCPOP_MCC20			0xDF
#define VCPOP_SMARTIMAGE	0xDC
#define VCPOP_PHP_RESOLU	0xE9 //0xF6
#define VCPOP_AOC_CMD		0xFE
#define VCPOP_END			0xFF
#define VCPOP_BENQ_FACTORY	0xFF
#define VCPOP_AUDIO			0x62
#define VCPOP_MUTE			0x8D


//#ifdef NOVATEK_HDCP_WRITER
#define VCPOP_NVT_HDCP_START	0xED
#define VCPOP_NVT_HDCP_WRITE	0xEE
#define VCPOP_NVT_HDCP_CHKSUM	0xEF
//#endif

//	THEFT DETERRENCE
#define VCPOP_TD_ACCESSMODE		0xFA
#define VCPOP_TD_TIMEOUT		0xFB
#define VCPOP_TD_PIN_L			0xFC
#define VCPOP_TD_PIN_H			0xFD
#define VCPOP_TD_STATE			0xFE


void CheckDDC2Bi(void);
void Check2BiCmd(void);
void SendNullCmd(unsigned char SlaveAddr);
void SendACKCmd(void);
void SendNACKCmd(void);
void GetVCP_Feature(void);
void SetVCP_Feature(void);
void SetVCP_Capabilities(void);
void SaveCurrentSetting(void);
void GetTiming(void);
void WaitVsync(void);


void BenQ_EnterFactoryMode(void);
void ReleaseFactoryMode(void);
void SendResponseCmd(void);


//#define RGB_OFFSET_MIN   92
//#define RGB_OFFSET_MAX  164
//#define RGB_OFFSET_SCOPE 72  //(RGB_OFFSET_MAX-RGB_OFFSET_MIN)



#define BenQ_ADDR	0x7c	// for BenQ Utility Alignment command




void TD_Init();
void WaitDDCTxOut();


#endif
