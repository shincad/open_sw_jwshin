using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

// add code
using System.IO;
using System.IO.Ports;

namespace SimpleSerialTest
{
    public partial class Form1 : Form
    {
        delegate void SetTextCallback(string Text);

        public Form1()
        {
            InitializeComponent();

            // Update Port List
            cbComPort.BeginUpdate();
            foreach (string comport in SerialPort.GetPortNames())
                cbComPort.Items.Add(comport);
            cbComPort.EndUpdate();

            // Initialize Serial Port
            serialPort1.BaudRate = 115200;
            serialPort1.DataBits = 8;
            serialPort1.Parity = Parity.None;
            serialPort1.StopBits = StopBits.One;

            // Configure Form1 Controls
            btnPortClose.Enabled = false;

            // Select First Control
            cbComPort.Select();
        }

        private void btnPortOpen_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.Open();
            }
            catch
            {
                tsslblStatus.Text = "해당 포트는 사용 중입니다.";
                return;
            }

            if (serialPort1.IsOpen)
            {
                tsslblStatus.Text = "포트가 연결되었습니다.";
                btnPortOpen.Enabled = false;
                btnPortClose.Enabled = true;
                EnableControls(false);
            }
            else
                tsslblStatus.Text = "포트를 연결하지 못했습니다.";
        }
        
        private void btnPortClose_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            tsslblStatus.Text = "포트 연결을 해제하였습니다.";
            btnPortOpen.Enabled = true;
            btnPortClose.Enabled = false;
            EnableControls(true);
        }

        private void btnDataSend_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                if (tbDataSend.Text.Length == 0)
                {
                    tsslblStatus.Text = "값을 입력하시오.";
                    return;
                }

                byte[] values = new byte[1];

                try
                {
                    if (rbDecSend.Checked == true)
                        values[0] = byte.Parse(tbDataSend.Text);
                    else if (rbHexSend.Checked == true)
                        values[0] = Convert.ToByte(tbDataSend.Text, 16);
                    else
                        values[0] = byte.Parse(tbDataSend.Text);
                }
                catch
                {
                    tsslblStatus.Text = "유효한 값이 아닙니다.";
                    return;
                }

                serialPort1.Write(values, 0, 1);
                tsslblStatus.Text = "데이터를 전송하였습니다.";               
            }
            else
            {
                tsslblStatus.Text = "포트 연결 후 다시 시도하십시오.";
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                string data = serialPort1.ReadExisting();

                if (data != string.Empty)
                {
                    char[] values = data.ToCharArray();
                    int value = Convert.ToInt32(values[0]);

                    if (rbDecRecv.Checked == true)
                        data = value.ToString();
                    else if(rbHexRecv.Checked == true)
                        data = "0x"+value.ToString("X2");
                    
                    DataProcessing(data);
                }
            }
        }

        private void DataProcessing(string Text)
        {
            if (this.tbDataRecv.InvokeRequired)
            {
                SetTextCallback dp = new SetTextCallback(DataProcessing);
                this.Invoke(dp, new object[] { Text });
            }
            else
            {
                this.tbDataRecv.Text += (Text + " ");
            }
        }

        private void EnableControls(bool value)
        {
            if (value == true)
            {
                cbComPort.Enabled = true;
                cbBaudRate.Enabled = true;
                cbDataBits.Enabled = true;
                cbParity.Enabled = true;
                cbStopBits.Enabled = true;
            }
            else
            {
                cbComPort.Enabled = false;
                cbBaudRate.Enabled = false;
                cbDataBits.Enabled = false;
                cbParity.Enabled = false;
                cbStopBits.Enabled = false;
            }
        }

        private void cbComPort_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.PortName = cbComPort.SelectedItem.ToString();
        }

        private void cbBaudRate_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (cbBaudRate.SelectedIndex)
            {
                case 0:
                    serialPort1.BaudRate = 9600; break;
                case 1:
                    serialPort1.BaudRate = 14400; break;
                case 2:
                    serialPort1.BaudRate = 19200; break;
                case 3:
                    serialPort1.BaudRate = 38400; break;
                case 4:
                    serialPort1.BaudRate = 57600; break;
                case 5:
                    serialPort1.BaudRate = 115200; break;
                case 6:
                    serialPort1.BaudRate = 128000; break;
                default:
                    serialPort1.BaudRate = 115200; break;
            }
        }

        private void cbDataBits_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (cbDataBits.SelectedIndex)
            {
                case 0:
                    serialPort1.DataBits = 8; break;
                case 1:
                    serialPort1.DataBits = 7; break;
                default:
                    serialPort1.DataBits = 8; break;
            }
        }

        private void cbParity_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (cbParity.SelectedIndex)
            {
                case 0:
                    serialPort1.Parity = Parity.Even; break;
                case 1:
                    serialPort1.Parity = Parity.Mark; break;
                case 2:
                    serialPort1.Parity = Parity.None; break;
                case 3:
                    serialPort1.Parity = Parity.Odd; break;
                case 4:
                    serialPort1.Parity = Parity.Space; break;
                default:
                    serialPort1.Parity = Parity.None; break;
            }
        }

        private void cbStopBits_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (cbStopBits.SelectedIndex)
            {
                case 0:
                    tsslblStatus.Text = "이 값은 지원되지 않습니다."; break;
                case 1:
                    serialPort1.StopBits = StopBits.One; break;
                case 2:
                    serialPort1.StopBits = StopBits.OnePointFive; break;
                case 3:
                    serialPort1.StopBits = StopBits.Two; break;
                default:
                    serialPort1.StopBits = StopBits.One; break;
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            tbDataRecv.Text = "";
        }
    }
}
