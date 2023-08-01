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
using EzioDll;

namespace Test_170205
{
    public partial class Form3 : Form
    {
        //-------------- 전달받을 폼의 Class에만 선언한다.
        public static string Send_Num_Dark { get; set; }
        public static string Send_Num_GapFeed { get; set; }
        public static string Send_Num_Height { get; set; }
        public static string Send_Num_LMargin { get; set; }
        public static string Send_Num_Speed { get; set; }
        public static string Send_Num_TMargin { get; set; }
        public static string Send_Num_Width { get; set; }
        public static string Send_Num_SHeight { get; set; }
        public static string Send_Num_SWidth { get; set; }
        public static string Send_Num_IsLarge { get; set; }

        public static string Num_IsLarge;

        public Form3()
        {
            InitializeComponent();
        }
        public void Form3_Load(object Sender, EventArgs e)
        {
            
            Num_Dark.Text = Send_Num_Dark; 
            Num_GapFeed.Text = Send_Num_GapFeed;
        //    Num_Height.Text = Send_Num_Height;
            Num_LeftMargin.Text = Send_Num_LMargin;
            Num_Speed.Text = Send_Num_Speed;
            Num_TopMargin.Text = Send_Num_TMargin;
        //    Num_Width.Text = Send_Num_Width;

            Num_IsLarge = Send_Num_IsLarge;
            
            if(Num_IsLarge=="1")
            {
                Num_Height.Text = Send_Num_Height;
                Num_Width.Text = Send_Num_Width; 
            }
            else
            {
                Num_Height.Text = Send_Num_SHeight;
                Num_Width.Text = Send_Num_SWidth;
            }



            Cbo_PaperType.SelectedIndex = 0;
            Properties.Settings.Default.Label_PaperType = "0";
                
        }

        private void Btn_SettingClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Btn_SettingSave_Click(object sender, EventArgs e)
        {
            
            Properties.Settings.Default.Label_Dark = Num_Dark.Text;
            Properties.Settings.Default.Label_GapFeed = Num_GapFeed.Text;
            //Properties.Settings.Default.Label_Height = Num_Height.Text;
            Properties.Settings.Default.Label_LMargin = Num_LeftMargin.Text;
            Properties.Settings.Default.Label_Speed = Num_Speed.Text;
            Properties.Settings.Default.Label_TMargin = Num_TopMargin.Text;
            //Properties.Settings.Default.Label_Width = Num_Width.Text;
            Properties.Settings.Default.Label_Dark = Num_Dark.Text;

            if(Num_IsLarge=="1")
            {
                Properties.Settings.Default.Label_Height = Num_Height.Text;
                Properties.Settings.Default.Label_Width = Num_Width.Text;
            }
            else
            {
                Properties.Settings.Default.Label_SHeight = Num_Height.Text;
                Properties.Settings.Default.Label_SWidth = Num_Width.Text;
            }

            Properties.Settings.Default.Save();

        }
    }
}
