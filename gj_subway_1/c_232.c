/* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */
/* H									H */
/* H	     TMS-32 V1.0 : RS-232C Serial Communication Program		H */
/* H									H */
/* H		    Programmed by Duck-Yong Yoon in 1998		H */
/* H									H */
/* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */

#include "CSTARTUP.C"

#include "atc.h"

/* ==================================================================== */
/*	User-Defined Functions						*/
/* ==================================================================== */


/* ==================================================================== */
/*	Main Program							*/
/* ==================================================================== */
void main()
{ int counter = 1, character;

  Init_DSP(); Delay_ms(50);			/* initialize DSP, 8255A, LCD */
  Init_8255();
  Init_LCD();
  Init_8251();					/* initialize 8251A */
  Beep();

	s_printf("atc td block text %f\n",3.141592);
	for(;1;)
	{
		PUTCHAR(GETCHAR());
		
		}
		
  LCD_data(0xFF);				/* display title */
  LCD_string(0x81, " RS-232C TEST ");
  LCD_data(0xFF);
  LCD_command(0x0F);				/* set cursor ON */
  LCD_command(0xC0);				/* set cursor position */

  TX_char(0x0D); TX_char(0x0A);
  TX_string("***** TMS-32 RS-232C Test *****");
  TX_char(0x0D); TX_char(0x0A);

  for(;;)
    { switch(Key_input())			/* key input and transmit message */
        { case 0x0E : *PPI_PC = 0x01;
                      TX_char(0x0D); TX_char(0x0A);
                      TX_string("<< SW1 >> ");
                      TX_string("TMS-32 8251A Serial Communication Test OK ! ");
                      Beep();
                      break;
          case 0x0D : *PPI_PC = 0x02;
                      TX_char(0x0D); TX_char(0x0A);
                      TX_string("<< SW2 >> ");
                      TX_string("TMS-32 8251A Serial Communication Test OK ! ");
                      Beep();
                      break;
          case 0x0B : *PPI_PC = 0x04;
                      TX_char(0x0D); TX_char(0x0A);
                      TX_string("<< SW3 >> ");
                      TX_string("TMS-32 8251A Serial Communication Test OK ! ");
                      Beep();
                      break;
          case 0x07 : *PPI_PC = 0x08;
                      TX_char(0x0D); TX_char(0x0A);
                      TX_string("<< SW4 >> ");
                      TX_string("TMS-32 8251A Serial Communication Test OK ! ");
                      Beep();
                      break;
          default   : break;
        }

      character = RX_char();				/* receive a character by 8251A */
      if((0x7F & character) >= 0x20)		/* legal LCD character ? */
        { LCD_data(character);				/* display a received character on LCD */
          counter++;
          if(counter == 17)					/* if the end of line, go first column */
            { counter = 1;
              LCD_command(0xC0); Beep();
            }
        }
    }
}
