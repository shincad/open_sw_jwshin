/****************************************************************************/
/*																			*/
/*			Serial Process													*/
/*																			*/
/*			Copyright	:: Phoenix Information Technology					*/
/*			Cpu			:: SH3												*/
/*			Language	:: SHC												*/
/*			File Name	:: comm.c											*/
/*																			*/
/****************************************************************************/
#include "def.h"
#include "ext.h"
#include "comm.h"
#include "sci.h"

#define CmdBufferSize	0x0080
#define Error			0x02

#define Null			0x00
#define LF				0x0A

/*	Variable Declaration	*/
unsigned char cmd_buffer[CmdBufferSize];
unsigned short cmd_buffer_pointer;

unsigned char dl_buffer[CmdBufferSize];
unsigned short dl_buffer_pointer;

enum CmdType
{
	WaitCommand,
	WriteCommand,
	DLCommand,
	BootWrCommand,
	CmdMax
};

enum CmdType comm_mode;

const unsigned char * const CmdString[CmdMax] =
{
	"",
	"WR",
	"DL",
	"BW",
};

unsigned long last_address;

/*	Function Prototype Declaration 	*/
static short download(unsigned char data);
static short check_sformat();
static void verify_ram2flash();
static void send_data(unsigned char data);


/*	Comm Process Init	*/
void comm_init()
{
	unsigned short i;

	comm_mode = WaitCommand;
	
	cmd_buffer_pointer = Null;

	for (i=0;i<CmdBufferSize;i++)
	{
		dl_buffer[i] = Null;
	}
	
	dl_buffer_pointer = 0;
	
	sci_init();
}

/*	Comm Process	*/
void comm_proc(unsigned char data)
{
	unsigned short i;
	short tmp;

	switch(comm_mode)
	{
		case WaitCommand:
			if (data == LF)
			{
				send_data(data);
				for (i=1;i<(unsigned short)CmdMax;i++)
				{
					if (str_comp((unsigned char *)CmdString[i],cmd_buffer) == ON)
					{
						comm_mode = (enum CmdType)i;
						i = (unsigned short)CmdMax;
					}
				}
				
				cmd_buffer_pointer = 0;
				
				for (i=0;i<CmdBufferSize;i++)
				{
					cmd_buffer[i] = Null;
				}
				if (comm_mode == DLCommand)
				{
					last_address = 0;
				}
			}
			else if (cmd_buffer_pointer < CmdBufferSize)
			{
				cmd_buffer[cmd_buffer_pointer] = data;
				cmd_buffer_pointer++;
				send_data(data);
			}
			break;
		case DLCommand:
			tmp = download(data);
			if (tmp == ON)
			{
				if (comm_mode != DLCommand)
				{
					send_data('e');
					send_data(LF);
				}
				else
				{
					send_data('x');
					send_data(LF);
				}
			}
			else if (tmp == Error)
			{
				send_data('m');
				send_data(LF);
				comm_mode = WaitCommand;
			}
			break;
		case WriteCommand:
			flash_erase_all();
			
			flash_write_proc((unsigned short *)StartAddressRam
							,(unsigned short *)StartAddressFlash
							,(last_address - StartAddressRam));
			
			send_data('W');
			send_data('R');
			send_data('E');
			send_data(LF);
			
			comm_mode = WaitCommand;
			
			verify_ram2flash();
			
			break;
		default:
			cmd_buffer_pointer = 0;
			
			for (i=0;i<CmdBufferSize;i++)
			{
				cmd_buffer[i] = Null;
			}
			
			comm_mode = WaitCommand;
			break;
	}
}

/*	Data Transmit	*/
static short download(unsigned char data)
{
	short i;
	short ans;

	if (data == LF)
	{
		ans = check_sformat();
		for (i=0;i<CmdBufferSize;i++)
		{
			dl_buffer[i] = Null;
		}
		dl_buffer_pointer = 0;
	}
	else
	{
		dl_buffer[dl_buffer_pointer] = data;
		dl_buffer_pointer++;
		ans = OFF;
	}
	return ans;
}

/*	Verify	*/
static void verify_ram2flash()
{
	unsigned char *add_DRAM;
	unsigned char *add_FROM;
	unsigned long i;

	add_DRAM = (unsigned char *)StartAddressRam;
	add_FROM = (unsigned char *)StartAddressFlash;
	for(i=0 ;i < EndAddressRam - StartAddressRam ;i++)
	{
		if( *add_DRAM + i != *add_FROM +i )
		{
			break;
		}
	}
}


/*	S-Format Analysis	*/
static short check_sformat()
{
	short ans;
	short l_byte;
	short length;
	unsigned long address;
	short s_pointer;
	short d_pointer;
	unsigned char data[0x0040];
	short i;
	unsigned char tmp;
	unsigned short sum;

	ans = ON;
	if (str_comp((unsigned char *)"END",dl_buffer) == ON)
	{
		ans = ON;
		comm_mode = WaitCommand;
	}
	else
	{
		if (dl_buffer[0] == 'S')
		{
			switch(dl_buffer[1])
			{
				case '1':
					l_byte = 4 / 2;
					break;
				case '2':
					l_byte = 6 / 2;
					break;
				case '3':
					l_byte = 8 / 2;
					break;
				default:
					l_byte = 0;
					break;
			}
			if (l_byte != 0)
			{
				s_pointer = 2;
				d_pointer = 0;
				while(dl_buffer[s_pointer] != Null)
				{
					tmp = (unsigned char)dl_buffer[s_pointer];
					if (tmp < 'A')
					{
						tmp &= 0x0f;
					}
					else
					{
						tmp = (tmp & 0x0f) + 0x0a - 1;
					}
					if (Odd(s_pointer))
					{
						data[d_pointer] += tmp;
						d_pointer++;
					}
					else
					{
						data[d_pointer] = tmp * 0x10;
					}
					s_pointer++;
				}
				length = data[0];
				address = 0;
				for (i=0;i<l_byte;i++)
				{
					address *= 0x00000100;
					address += data[i+1];
				}

				sum = 0;
				for (i=0;i<length+1;i++)
				{
					sum += data[i];
				}
				if ((sum & 0x00ff) == 0x00ff)
				{
					address &= 0x1FFFFFFF;
					address = address + StartAddressRam;	/*  Inter RAM Address Offset  */
					for (i=l_byte+1;i<length;i++)
					{
						if(address > EndAddressRam) address = EndAddressRam;
						*((unsigned char *)(address)) = data[i];
						address++;
					}
					
					if (last_address < address)
					{
						last_address = address;
					}
					
					ans = ON;
				}
				else
				{
					ans = Error;
					send_data((char)(sum / 0x0100));
					send_data((char)(sum & 0x00FF));
				}
			}
		}
	}
	return ans;
}

/*	String Compare	*/
unsigned short str_comp(unsigned char * str1,unsigned char * str2)
{
	short i;
	unsigned short ans;

	ans = ON;
	i = 0;
	while((str1[i] != 0x00) && (ans == ON))
	{
		if (str1[i] != str2[i])
		{
			ans = OFF;
		}
		i++;
	}
	return ans;
}


/*	Data Transmit Function	*/
static void send_data(unsigned char data)
{
	set_send_data(CommSCIF,data);
}
