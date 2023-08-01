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
    public partial class Frm_PrinterSetting : Form
    {
        public static string Send_USB { get; set; }
        public static string Send_Drv_Item { get; set; }
        public static string Send_Drv_Select { get; set; }

        public Frm_PrinterSetting()
        {
            InitializeComponent();


        }
        public void Frm_PrinterSetting_Load(object Sender, EventArgs e)
        {
            
            bool bUSB;
            bool bDrv_Select;
             

            if(Send_USB == "True")
            {
                bUSB = true;
            }
            else
            {
                bUSB = false;
            }
            if(Send_Drv_Select=="True")
            {
                bDrv_Select = true;
            }
            else
            {
                bDrv_Select = false;
            }
         

            if(bUSB)
            {
                RBtn_USB.Select();
            }
            if(bDrv_Select)
            {
                RBtn_Drv.Select();
            }
           
            
            string[] DriverPrinter = GodexPrinter.GetDriverPrinter();
            if (DriverPrinter != null)
            {
                Cbo_Drv.Items.Clear();
                for (int i = 0; i < DriverPrinter.Length; i++)
                {
                    Cbo_Drv.Items.Add(DriverPrinter[i]);
                }
                if (Cbo_Drv.Items.Count > 0)
                {
                    Cbo_Drv.SelectedIndex = 0;
                }
            }


            /*
            if(Properties.Settings.Default.USB)
            {
                RBtn_USB.Select();
            }
            if(Properties.Settings.Default.Drv_Select)
            {
                RBtn_Drv.Select();
            }

            string[] DriverPrinter = GodexPrinter.GetDriverPrinter();
            if(DriverPrinter != null)
            {
                Cbo_Drv.Items.Clear();
                for(int i=0;i<DriverPrinter.Length;i++)
                {
                    Cbo_Drv.Items.Add(DriverPrinter[i]);
                }
                if(Cbo_Drv.Items.Count>0)
                {
                    Cbo_Drv.SelectedIndex = 0;
                }
            }
            */
        }



        private void RBtn_USB_CheckedChanged(object sender, EventArgs e)
        {
        
            RBtn_USB.Select();
          
            Properties.Settings.Default.USB = true;
        }

        private void RBtn_Drv_CheckedChanged(object sender, EventArgs e)
        {
          
            RBtn_Drv.Select();
           
            Properties.Settings.Default.Drv_Select = true;
        }

        private void Btn_Close_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Cbo_Drv_SelectedIndexChanged(object sender, EventArgs e)
        {
            Properties.Settings.Default.Drv_Item = Cbo_Drv.SelectedItem.ToString();
        }

        private void Btn_PortSave_Click(object sender, EventArgs e)
        {
            if(RBtn_USB.Checked)
            {
                Properties.Settings.Default.USB = true;
            }
            else
            {
                Properties.Settings.Default.USB = false;
            }
            if(RBtn_Drv.Checked)
            {
                Properties.Settings.Default.Drv_Select = true;
            }
            else
            {
                Properties.Settings.Default.Drv_Select = false;
            }
        }
    }
}
