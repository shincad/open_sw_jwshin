//**************************************************************************
//
//		SProcessor.h
//    	AUDIO processor source
//   		made by  BTC Korea.  R&D Lab.   Youngdo Cho
//		Start at 2003.7.8
//
//**************************************************************************


#if !defined _NFREN_SOUND_PROCESSOR_
#define _NFREN_SOUND_PROCESSOR_

#define	SPROCRSSOR_NON	0
#define	SPROCRSSOR_MSP3415	0x01+0x80
#define	SPROCRSSOR_MSP3410	0x07+0x80
#define	SPROCRSSOR_MSP3425	0x21+0x80
#define	SPROCRSSOR_MSP3420	0x27+0x80

#define MSP34xy_Addr		0x80


#define SoundType_MONO			0
#define SoundType_STEREO		1
#define SoundType_SAP			2

//WORD SoundGetStandard(void)	;

bit MSP34xyDSPWrite(unsigned char SubAddr,unsigned int RegAddr,unsigned int Data);

void SoundInit();
void SoundProcess();
void SoundInputSelection(unsigned char input);
void ScartSwitch(unsigned int ACBRegister);

unsigned char SoundGetStatus();
void SoundSet(void);
void SetFMmatrix(unsigned char value) ;
void SaveCurrentSSCToUser();
void SoundSetBass(void)	;
void SoundSetTreble(void)	;
void SoundSetLoudness(void)	;
void SoundSetVolume(void);	// smpark 20030923
void SoundFastMute(void);	// smpark 20030925
void SetToMono(void);

void StereoSet(void);			// smpark 20030825
void BilingualSet(void);		// smpark 20030825

#ifdef Mono_Sound
#define  SoundSetMono()		SetFMmatrix(0x00)//SetFMmatrix(0x03)
#else
#define  SoundSetMono()		SetFMmatrix(0x03)	//0x000E
#endif
#define SoundSetStereo()	SetFMmatrix(0x02)
#define SoundSetMTSmain()	SetFMmatrix(0x03)	// Bilingual A
#define SoundSetMTSsub()	SetFMmatrix(0x04)	// Bilingual B
#define SoundSetMTSmix()	SetFMmatrix(0x00)	// Bilingual A+B

#endif
