/*
1. 50Hz�� ���� H,v��.
2. 60Hz�� ���� H,v��.
3. EMH1A,EMH2�� �϶��� ���� H,V��ġ��.
4. ���� ���� ���⶧�� H,V��ġ��.
5. ���� ������ �ƴҶ��� H,V��ġ��.
6. NTSC,PAL�϶��� H,V��ġ��.
*/

//50Hz <-> 60Hz ���������.
#if defined(EMH1A)
	#if defined(SAA7114)||defined(SAA7115)
		#if defined(SXGA_Panel)
			#define	IBHAS_Main50Hz_value					115
			#define	IBHAS_Main60Hz_value					107		
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#elif defined(XGA_Panel)
			#define	IBHAS_Main50Hz_value					115	
			#define	IBHAS_Main60Hz_value					107
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#elif defined(SVGA_Panel)
			#define	IBHAS_Main50Hz_value					115
			#define	IBHAS_Main60Hz_value					107	
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#endif
	#elif defined(VPC323x)
		#if defined(SXGA_Panel)
			#define	IBHAS_Main50Hz_value					116	
			#define	IBHAS_Main60Hz_value					108
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#elif defined(XGA_Panel)
			#define	IBHAS_Main50Hz_value					116	
			#define	IBHAS_Main60Hz_value					108
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#elif defined(SVGA_Panel)
			#define	IBHAS_Main50Hz_value					116	
			#define	IBHAS_Main60Hz_value					108
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#endif
	#endif
#elif defined(EMH2)
	#if defined(SAA7114)||defined(SAA7115)
		#if defined(SXGA_Panel)
			#define	IBHAS_Main50Hz_value					115		
			#define	IBHAS_Main60Hz_value					107
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#elif defined(XGA_Panel)
			#define	IBHAS_Main50Hz_value					115		
			#define	IBHAS_Main60Hz_value					107
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#elif defined(SVGA_Panel)
			#define	IBHAS_Main50Hz_value					115		
			#define	IBHAS_Main60Hz_value					107
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#endif
	#elif defined(VPC323x)
		#if defined(SXGA_Panel)
			#define	IBHAS_Main50Hz_value					115
			#define	IBHAS_Main60Hz_value					107	
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#elif defined(XGA_Panel)
			#define	IBHAS_Main50Hz_value					115		
			#define	IBHAS_Main60Hz_value					107
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#elif defined(SVGA_Panel)
			#define	IBHAS_Main50Hz_value					115		
			#define	IBHAS_Main60Hz_value					107
			#define	IBVAS_Main50Hz_value					37
			#define	IBVAS_Main60Hz_value					18
		#endif
	#elif defined(TW9908)
		#if defined(SXGA_Panel)
			#define	IBHAS_Main50Hz_value					56//
			#define	IBHAS_Main60Hz_value					58//	
			#define	IBVAS_Main50Hz_value					18//20
			#define	IBVAS_Main60Hz_value					14//15//
		#elif defined(WXGA_Panel)
			#define	IBHAS_Main50Hz_value					54//
			#define	IBHAS_Main60Hz_value					56//58//	
			#define	IBVAS_Main50Hz_value					18//20
			#define	IBVAS_Main60Hz_value					14//15//
		#elif defined(XGA_Panel)
			#define	IBHAS_Main50Hz_value					78		
			#define	IBHAS_Main60Hz_value					78
			#define	IBVAS_Main50Hz_value					20
			#define	IBVAS_Main60Hz_value					12
		#elif defined(SVGA_Panel)
			#define	IBHAS_Main50Hz_value					78
			#define	IBHAS_Main60Hz_value					78
			#define	IBVAS_Main50Hz_value					20
			#define	IBVAS_Main60Hz_value					12
		#else
			#define	IBHAS_Main50Hz_value					56
			#define	IBHAS_Main60Hz_value					58
			#define	IBVAS_Main50Hz_value					18
			#define	IBVAS_Main60Hz_value					14
		#endif
		
	#endif
#endif


//Fixed H-position.
#if defined(EMH1A)
	#ifdef	DrowCircle
		#if defined(USE_NTSCtuner)
			#if defined(SXGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	135	
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value		
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#endif
			#elif defined(XGA_Panle)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#endif
			#elif defined(SVGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#endif
			#endif
		#elif defined(USE_PALSECAMtuner)
			#if defined(SXGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	139
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	139
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#endif
			#elif defined(XGA_Panle)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	139
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	139
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#endif
			#elif defined(SVGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	139
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	139
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#endif
			#endif
		#endif
	#else
		#if defined(USE_NTSCtuner)
			#if defined(SXGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	107
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	108
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#endif
			#elif defined(XGA_Panle)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	109
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	110
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#endif
			#elif defined(SVGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	109
					#define	IBVAS_Main_value	27
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	110
					#define	IBVAS_Main_value	27
					#define	IBHAS_PIP_value
				#endif
			#endif
		#elif defined(USE_PALSECAMtuner)
			#if defined(SXGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	107
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#endif
			#elif defined(XGA_Panle)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	109
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#endif
			#elif defined(SVGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	109
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#endif
			#endif
		#endif		
	#endif
#elif defined(EMH2)
	#if defined(DrowCircle)
		#if defined(USE_NTSCtuner)
			#if defined(SXGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value					
				#endif
			#elif defined(XGA_Panle)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#elif defined(SVGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	135
					#define	IBVAS_Main_value	18
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#endif
		#elif defined(USE_PALSECAMtuner)
			#if defined(SXGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	139
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#elif defined(XGA_Panle)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	139
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	139
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#elif defined(SVGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	139
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#endif
		#endif
	#else
		#if defined(USE_NTSCtuner)
			#if defined(SXGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	107
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	108
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#elif defined(XGA_Panle)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	109
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	110
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#elif defined(SVGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	109
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	110
					#define	IBVAS_Main_value	26
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#endif
		#elif defined(USE_PALSECAMtuner)
			#if defined(SXGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	115
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	116
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#elif defined(XGA_Panle)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	115
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBVAS_Main_value	37
					#define	IBHAS_Main_value	116
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#elif defined(SVGA_Panel)
				#if defined(SAA7114)||defined(SAA7115)
					#define	IBHAS_Main_value	115
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#elif defined(VPC323x)
					#define	IBHAS_Main_value	116
					#define	IBVAS_Main_value	37
					#define	IBHAS_PIP_value
				#elif defined(TW9908)
					#define	IBHAS_Main_value	78
					#define	IBVAS_Main_value	12
					#define	IBHAS_PIP_value							
				#endif
			#endif
		#endif		
	#endif
#endif
