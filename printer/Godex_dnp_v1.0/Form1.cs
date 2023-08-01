using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO.Ports;
using EzioDll;


namespace Test_170205
{

   
    public partial class Form1 : Form
    {
        GodexPrinter Printer = new GodexPrinter();

     //   public static string Send_Num_Dark { get; set; }



        int[] CodePage_Code = { 0,
            864, 708, 720, 28596, 10004, 1256, 775, 28594, 1257, 852,                               // 01
            28592, 10029, 1250, 51936, 54936, 936, 20936, 52936, 50227, 10008,                      // 02
            950, 20000, 20002, 10002, 10082, 866, 28595, 20866, 21866, 10007,                       // 03
            1251, 28603, 29001, 863, 20106, 737, 28597, 10006, 1253, 869,                           // 04
            862, 38598, 28598, 10005, 1255, 20420, 20880, 21025, 20277, 1142,                       // 05
            20278, 1143, 20297, 1147, 20273, 1141, 875, 20423, 20424, 20871,                        // 06
            1149, 500, 1148, 20280, 1144, 20290, 20833, 870, 20284, 1145,                           // 07
            20838, 1026, 20905, 20285, 1146, 37, 1140, 1047, 20924, 20003,                          // 08
            861, 10079, 57006, 57003, 57002, 57010, 57008, 57009, 57007, 57011,                     // 09
            57004, 57005, 20269, 51932, 20932, 50220, 50222, 50221, 10001, 932,                     // 10
            949, 51949, 50225, 1361, 10003, 20949, 28593, 28605, 865, 20108,                        // 11
            855, 858, 437, 860, 10010, 20107, 20261, 20001, 20004, 10021,                           // 12
            874, 857, 28599, 10081, 1254, 10017, 1200, 1201, 12001, 12000,                          // 13
            65000, 65001, 20127, 1258, 20005, 850, 20105, 28591, 10000, 1252};                      // 14

        string[] CodePage_Name = { "System Default",
            "IBM864", "ASMO-708", "DOS-720", "iso-8859-6", "x-mac-arabic", "windows-1256", "ibm775", "iso-8859-4", "windows-1257", "ibm852",                    // 01
            "iso-8859-2", "x-mac-ce", "windows-1250", "EUC-CN", "GB18030", "gb2312", "x-cp20936", "hz-gb-2312", "x-cp50227", "x-mac-chinesesimp",               // 02
            "big5", "x-Chinese-CNS", "x-Chinese-Eten", "x-mac-chinesetrad", "x-mac-croatian", "cp866", "iso-8859-5", "koi8-r", "koi8-u", "x-mac-cyrillic",      // 03
            "windows-1251", "iso-8859-13", "x-Europa", "IBM863", "x-IA5-German", "ibm737", "iso-8859-7", "x-mac-greek", "windows-1253", "ibm869",               // 04
            "DOS-862", "iso-8859-8-i", "iso-8859-8", "x-mac-hebrew", "windows-1255", "IBM420", "IBM880", "cp1025", "IBM277", "IBM01142",                        // 05
            "IBM278", "IBM01143", "IBM297", "IBM01147", "IBM273", "IBM01141", "cp875", "IBM423", "IBM424", "IBM871",                                            // 06
            "IBM01149", "IBM500", "IBM01148", "IBM280", "IBM01144", "IBM290", "x-EBCDIC-KoreanExtended", "IBM870", "IBM284", "IBM01145",                        // 07
            "IBM-Thai", "IBM1026", "IBM905", "IBM285", "IBM01146", "IBM037", "IBM01140", "IBM01047", "IBM00924", "x-cp20003",                                   // 08
            "ibm861", "x-mac-icelandic", "x-iscii-as", "x-iscii-be", "x-iscii-de", "x-iscii-gu", "x-iscii-ka", "x-iscii-ma", "x-iscii-or", "x-iscii-pa",        // 09
            "x-iscii-ta", "x-iscii-te", "x-cp20269", "euc-jp", "EUC-JP", "iso-2022-jp", "iso-2022-jp", "csISO2022JP", "x-mac-japanese", "shift_jis",            // 10
            "ks_c_5601-1987", "euc-kr", "iso-2022-kr", "Johab", "x-mac-korean", "x-cp20949", "iso-8859-3", "iso-8859-15", "IBM865", "x-IA5-Norwegian",          // 11
            "IBM855", "IBM00858", "IBM437", "IBM860", "x-mac-romanian", "x-IA5-Swedish", "x-cp20261", "x-cp20001", "x-cp20004", "x-mac-thai",                   // 12
            "windows-874", "ibm857", "iso-8859-9", "x-mac-turkish", "windows-1254", "x-mac-ukrainian", "utf-16", "unicodeFFFE", "utf-32BE", "utf-32",           // 13
            "utf-7", "utf-8", "us-ascii", "windows-1258", "x-cp20005", "ibm850", "x-IA5", "iso-8859-1", "macintosh", "Windows-1252" };                          // 14

        string[] CodePage_DispName = { "System Default",
            "Arabic (864)", "Arabic (ASMO 708)", "Arabic (DOS)", "Arabic (ISO)", "Arabic (Mac)",
            "Arabic (Windows)", "Baltic (DOS)", "Baltic (ISO)", "Baltic (Windows)", "Central European (DOS)",
            "Central European (ISO)", "Central European (Mac)", "Central European (Windows)", "Chinese Simplified (EUC)", "Chinese Simplified (GB18030)",
            "Chinese Simplified (GB2312)", "Chinese Simplified (GB2312-80)", "Chinese Simplified (HZ)", "Chinese Simplified (ISO-2022)", "Chinese Simplified (Mac)",
            "Chinese Traditional (Big5)", "Chinese Traditional (CNS)", "Chinese Traditional (Eten)", "Chinese Traditional (Mac)", "Croatian (Mac)",
            "Cyrillic (DOS)", "Cyrillic (ISO)", "Cyrillic (KOI8-R)", "Cyrillic (KOI8-U)", "Cyrillic (Mac)",
            "Cyrillic (Windows)", "Estonian (ISO)", "Europa", "French Canadian (DOS)", "German (IA5)",
            "Greek (DOS)", "Greek (ISO)", "Greek (Mac)", "Greek (Windows)", "Greek, Modern (DOS)",
            "Hebrew (DOS)", "Hebrew (ISO-Logical)", "Hebrew (ISO-Visual)", "Hebrew (Mac)", "Hebrew (Windows)",
            "IBM EBCDIC (Arabic)", "IBM EBCDIC (Cyrillic Russian)", "IBM EBCDIC (Cyrillic Serbian-Bulgarian)", "IBM EBCDIC (Denmark-Norway)", "IBM EBCDIC (Denmark-Norway-Euro)",
            "IBM EBCDIC (Finland-Sweden)", "IBM EBCDIC (Finland-Sweden-Euro)", "IBM EBCDIC (France)", "IBM EBCDIC (France-Euro)", "IBM EBCDIC (Germany)",
            "IBM EBCDIC (Germany-Euro)", "IBM EBCDIC (Greek Modern)", "IBM EBCDIC (Greek)", "IBM EBCDIC (Hebrew)", "IBM EBCDIC (Icelandic)",
            "IBM EBCDIC (Icelandic-Euro)", "IBM EBCDIC (International)", "IBM EBCDIC (International-Euro)", "IBM EBCDIC (Italy)", "IBM EBCDIC (Italy-Euro)",
            "IBM EBCDIC (Japanese katakana)", "IBM EBCDIC (Korean Extended)", "IBM EBCDIC (Multilingual Latin-2)", "IBM EBCDIC (Spain)", "IBM EBCDIC (Spain-Euro)",
            "IBM EBCDIC (Thai)", "IBM EBCDIC (Turkish Latin-5)", "IBM EBCDIC (Turkish)", "IBM EBCDIC (UK)", "IBM EBCDIC (UK-Euro)",
            "IBM EBCDIC (US-Canada)", "IBM EBCDIC (US-Canada-Euro)", "IBM Latin-1", "IBM Latin-1", "IBM5550 Taiwan",
            "Icelandic (DOS)", "Icelandic (Mac)", "ISCII Assamese", "ISCII Bengali", "ISCII Devanagari",
            "ISCII Gujarati", "ISCII Kannada", "ISCII Malayalam", "ISCII Oriya", "ISCII Punjabi",
            "ISCII Tamil", "ISCII Telugu", "ISO-6937", "Japanese (EUC)", "Japanese (JIS 0208-1990 and 0212-1990)",
            "Japanese (JIS)", "Japanese (JIS-Allow 1 byte Kana - SO/SI)", "Japanese (JIS-Allow 1 byte Kana)", "Japanese (Mac)", "Japanese (Shift-JIS)",
            "Korean", "Korean (EUC)", "Korean (ISO)", "Korean (Johab)", "Korean (Mac)", "Korean Wansung",
            "Latin 3 (ISO)", "Latin 9 (ISO)", "Nordic (DOS)", "Norwegian (IA5)",
            "OEM Cyrillic", "OEM Multilingual Latin I", "OEM United States", "Portuguese (DOS)", "Romanian (Mac)",
            "Swedish (IA5)", "T.61", "TCA Taiwan", "TeleText Taiwan", "Thai (Mac)",
            "Thai (Windows)", "Turkish (DOS)", "Turkish (ISO)", "Turkish (Mac)", "Turkish (Windows)",
            "Ukrainian (Mac)", "Unicode", "Unicode (Big endian)", "Unicode (UTF-32 Big endian)", "Unicode (UTF-32)",
            "Unicode (UTF-7)", "Unicode (UTF-8)", "US-ASCII", "Vietnamese (Windows)", "Wang Taiwan",
            "Western European (DOS)", "Western European (IA5)", "Western European (ISO)", "Western European (Mac)", "Western European (Windows)" };



        public Form1()
        {
            InitializeComponent();
        }

    

        private void Form1_Load(object Sender, EventArgs e)
        {
            /* Form3 frm3 = new Form3();
             Form3.Send_Num_Dark = Properties.Settings.Default.Label_Dark;
             Form3.Send_Num_GapFeed = Properties.Settings.Default.Label_GapFeed;
             Form3.Send_Num_Height = Properties.Settings.Default.Label_Height;
             Form3.Send_Num_LMargin = Properties.Settings.Default.Label_LMargin;
             Form3.Send_Num_Speed = Properties.Settings.Default.Label_Speed;
             Form3.Send_Num_TMargin = Properties.Settings.Default.Label_TMargin;
             Form3.Send_Num_Width = Properties.Settings.Default.Label_Width;
            */   // 여기서 Form3쪽으로 전달값을 전달하면, Form3 Closing 후 다시 Form1으로 돌아올 때, Reloading 시 문제가 발생.

            Num_Page.Text = Properties.Settings.Default.Label_PrtCnt;
            Num_Copy.Text = Properties.Settings.Default.Label_PrtCopy;
            if(Properties.Settings.Default.Large_Barcode == "1")
            {
                Cbo_Large.Select();
            }
            else
            {
                Cbo_Small.Select();
            }

            if(Cbo_Large.Checked)
            {
                Txt_Barcode.Text = Properties.Settings.Default.Barcode_LText;
            }
            else
            {
                Txt_Barcode.Text = Properties.Settings.Default.Barcode_SText;
            }

              
        }
        //--------------------------- Connect Printer
        private void ConnectPrinter()
        {
            if(Properties.Settings.Default.USB == true)
            {
                Printer.Open(PortType.USB);
            }
            else if(Properties.Settings.Default.Drv_Select == true)
            {
                Printer.Open(Properties.Settings.Default.Drv_Item.ToString());
            }
        }

        private void DisconnectPrinter()
        {
            Printer.Close();
        }

        private void miPrinterSetting_Click(object sender, EventArgs e)
        {
            Frm_PrinterSetting dlg = new Frm_PrinterSetting();
            Frm_PrinterSetting.Send_USB = Properties.Settings.Default.USB.ToString();
            Frm_PrinterSetting.Send_Drv_Select = Properties.Settings.Default.Drv_Select.ToString();
            Frm_PrinterSetting.Send_Drv_Item = Properties.Settings.Default.Drv_Item.ToString();
          
            dlg.Show();
          

        }

        private Boolean NumCntCheck()
        {
            if(Cbo_Small.Checked == true)
            {
                if(Txt_Barcode.TextLength != 12)
                {
                    MessageBox.Show("자리 수를 12자리로 해 주세요.");
                    return false;
                }
                else
                {
                    return true;
                }
            }
            else if(Cbo_Large.Checked == true)
            {
                if(Txt_Barcode.TextLength != 18)
                {
                    MessageBox.Show("자리 수를 18자리로 해 주세요");
                    return false;
                }
                else
                {
                    return true;
                }
            }
            else
            {
                return true;
            }
        }


        private void LabelSetup()
        {
            if(Properties.Settings.Default.Large_Barcode == "1")
            {
                Printer.Config.LabelMode((PaperMode)0, Int32.Parse(Properties.Settings.Default.Label_Height) + 4, Int32.Parse(Properties.Settings.Default.Label_GapFeed));
                Printer.Config.LabelWidth(Int32.Parse(Properties.Settings.Default.Label_Width) + 4);
            }
            else
            {
                Printer.Config.LabelMode((PaperMode)0, Int32.Parse(Properties.Settings.Default.Label_SHeight) + 4, Int32.Parse(Properties.Settings.Default.Label_GapFeed));
                Printer.Config.LabelWidth(Int32.Parse(Properties.Settings.Default.Label_SWidth) + 4);
            }
            Printer.Config.Dark(Int32.Parse(Properties.Settings.Default.Label_Dark));
            Printer.Config.Speed(Int32.Parse(Properties.Settings.Default.Label_Speed));
            Printer.Config.PageNo(1);
            //  Printer.Config.CopyNo(Int32.Parse(Properties.Settings.Default.Label_PrtCopy));
            Printer.Config.CopyNo((int)Num_Copy.Value);
        }

        private void Send_LMargin()
        {
            int LMargin = Int32.Parse(Properties.Settings.Default.Label_LMargin)*8;
            String Temp = "^R" + LMargin.ToString();
           // ConnectPrinter();
            Printer.Command.Send(Temp);
           // Printer.Close();        
        }



        private void miSetting_Click(object sender, EventArgs e)
        {
            Form3 dlg = new Form3();
            Form3.Send_Num_Dark = Properties.Settings.Default.Label_Dark;
            Form3.Send_Num_GapFeed = Properties.Settings.Default.Label_GapFeed;
            Form3.Send_Num_Height = Properties.Settings.Default.Label_Height;
            Form3.Send_Num_LMargin = Properties.Settings.Default.Label_LMargin;
            Form3.Send_Num_Speed = Properties.Settings.Default.Label_Speed;
            Form3.Send_Num_TMargin = Properties.Settings.Default.Label_TMargin;
            Form3.Send_Num_Width = Properties.Settings.Default.Label_Width;
            Form3.Send_Num_SHeight = Properties.Settings.Default.Label_SHeight;
            Form3.Send_Num_SWidth = Properties.Settings.Default.Label_SWidth;
            Form3.Send_Num_IsLarge = Properties.Settings.Default.Large_Barcode;
            dlg.Show();
        }

        private void Btn_PrintBarcode_Click(object sender, EventArgs e)
        {
            if(!NumCntCheck())
            {
                return;
            }
            if(Cbo_Large.Checked == true)
            {
                
                String TextValue = Txt_Barcode.Text;
                String SerialValue_Low = TextValue.Substring(8, 10);
                String SerialValue_High = TextValue.Substring(0, 8);
                long NumSerial = long.Parse(SerialValue_Low);

                for (int LabelSerial = 0; LabelSerial < Num_Page.Value; LabelSerial++)
                {
                    int BarCode_YPos = (Int32.Parse(Properties.Settings.Default.Label_TMargin) * 8) + 131;
                    int Text_YPos = (Int32.Parse(Properties.Settings.Default.Label_TMargin) * 8) + 221;
                    ConnectPrinter();
                    LabelSetup();
                    Send_LMargin(); 
                    Printer.Command.Send("E9");
                    Printer.Command.Send("^XSET,ROTATION,0");
                    Printer.Command.Start();
                    String SendValue = (NumSerial + LabelSerial).ToString("D10");
                    Printer.Command.Send("BA3,34," + BarCode_YPos.ToString() + ",1,3,86,0,0," + "$" + SerialValue_High + SendValue);
                    Printer.Command.Send("ATA,24," + Text_YPos.ToString() + ",39,42,0,0E,A,0," + SerialValue_High + SendValue);
                    Printer.Command.End();
                    DisconnectPrinter();

                }



            }
            else
            {
                String TextValue = Txt_Barcode.Text;
                String SerialValue_Low = TextValue.Substring(8, 4);
                String SerialValue_High = TextValue.Substring(0, 8);
                long NumSerial = long.Parse(SerialValue_Low);


                for (int LabelSerial = 0; LabelSerial < Num_Page.Value; LabelSerial++)
                {
                    int BarCode_YPos = (Int32.Parse(Properties.Settings.Default.Label_TMargin) * 8) + 72;
                    int Text_YPos = (Int32.Parse(Properties.Settings.Default.Label_TMargin) * 8) + 137;
                    ConnectPrinter();
                    LabelSetup();
                    Send_LMargin();
                    Printer.Command.Send("^E12");
                    Printer.Command.Send("^XSET,ROTATION,0");
                    Printer.Command.Start();
                    String SendValue = (NumSerial + LabelSerial).ToString("D4");
                    Printer.Command.Send("BA3,23," + BarCode_YPos.ToString() + ",1,5,70,0,0," + "$" + SerialValue_High + SendValue);
                    Printer.Command.Send("ATA,53," + Text_YPos.ToString() + ",45,45,0,0E,A,0," + SerialValue_High + SendValue);
                    Printer.Command.End();
                    DisconnectPrinter();

                }

            }
        }

        private void Cbo_Small_CheckedChanged(object sender, EventArgs e)
        {
            Txt_Barcode.Text = "128058CE0001";
            Form3.Send_Num_IsLarge = "0";
            Properties.Settings.Default.Large_Barcode = "0";
        }

        private void Cbo_Large_CheckedChanged(object sender, EventArgs e)
        {
            Txt_Barcode.Text = "128058CE0000005101";
            Form3.Send_Num_IsLarge = "1";
            Properties.Settings.Default.Large_Barcode = "1";
        }

        private void Num_Copy_ValueChanged(object sender, EventArgs e)
        {
            Properties.Settings.Default.Label_PrtCopy = Num_Copy.Text;
            Properties.Settings.Default.Save();
        }

        private void Num_Page_ValueChanged(object sender, EventArgs e)
        {
            Properties.Settings.Default.Label_PrtCnt = Num_Page.Text;
            Properties.Settings.Default.Save();
        }

        private void miExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
