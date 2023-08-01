namespace SimpleSerialTest
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.gbSerialSetting = new System.Windows.Forms.GroupBox();
            this.btnPortClose = new System.Windows.Forms.Button();
            this.btnPortOpen = new System.Windows.Forms.Button();
            this.cbStopBits = new System.Windows.Forms.ComboBox();
            this.cbParity = new System.Windows.Forms.ComboBox();
            this.cbDataBits = new System.Windows.Forms.ComboBox();
            this.cbBaudRate = new System.Windows.Forms.ComboBox();
            this.cbComPort = new System.Windows.Forms.ComboBox();
            this.lblStopBits = new System.Windows.Forms.Label();
            this.lblDataBits = new System.Windows.Forms.Label();
            this.lblParity = new System.Windows.Forms.Label();
            this.lblBaudRate = new System.Windows.Forms.Label();
            this.lblComPort = new System.Windows.Forms.Label();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.tsslblStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.gbDataSend = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.rbAsciiSend = new System.Windows.Forms.RadioButton();
            this.rbHexSend = new System.Windows.Forms.RadioButton();
            this.rbDecSend = new System.Windows.Forms.RadioButton();
            this.btnDataSend = new System.Windows.Forms.Button();
            this.tbDataSend = new System.Windows.Forms.TextBox();
            this.gbDataRecv = new System.Windows.Forms.GroupBox();
            this.btnClear = new System.Windows.Forms.Button();
            this.tbDataRecv = new System.Windows.Forms.TextBox();
            this.rbAsciiRecv = new System.Windows.Forms.RadioButton();
            this.rbHexRecv = new System.Windows.Forms.RadioButton();
            this.rbDecRecv = new System.Windows.Forms.RadioButton();
            this.gbSerialSetting.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.gbDataSend.SuspendLayout();
            this.gbDataRecv.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbSerialSetting
            // 
            this.gbSerialSetting.Controls.Add(this.btnPortClose);
            this.gbSerialSetting.Controls.Add(this.btnPortOpen);
            this.gbSerialSetting.Controls.Add(this.cbStopBits);
            this.gbSerialSetting.Controls.Add(this.cbParity);
            this.gbSerialSetting.Controls.Add(this.cbDataBits);
            this.gbSerialSetting.Controls.Add(this.cbBaudRate);
            this.gbSerialSetting.Controls.Add(this.cbComPort);
            this.gbSerialSetting.Controls.Add(this.lblStopBits);
            this.gbSerialSetting.Controls.Add(this.lblDataBits);
            this.gbSerialSetting.Controls.Add(this.lblParity);
            this.gbSerialSetting.Controls.Add(this.lblBaudRate);
            this.gbSerialSetting.Controls.Add(this.lblComPort);
            this.gbSerialSetting.Location = new System.Drawing.Point(13, 13);
            this.gbSerialSetting.Name = "gbSerialSetting";
            this.gbSerialSetting.Size = new System.Drawing.Size(203, 259);
            this.gbSerialSetting.TabIndex = 0;
            this.gbSerialSetting.TabStop = false;
            this.gbSerialSetting.Text = "Serial Setting";
            // 
            // btnPortClose
            // 
            this.btnPortClose.Location = new System.Drawing.Point(108, 211);
            this.btnPortClose.Name = "btnPortClose";
            this.btnPortClose.Size = new System.Drawing.Size(75, 34);
            this.btnPortClose.TabIndex = 6;
            this.btnPortClose.Text = "Port Close";
            this.btnPortClose.UseVisualStyleBackColor = true;
            this.btnPortClose.Click += new System.EventHandler(this.btnPortClose_Click);
            // 
            // btnPortOpen
            // 
            this.btnPortOpen.Location = new System.Drawing.Point(18, 211);
            this.btnPortOpen.Name = "btnPortOpen";
            this.btnPortOpen.Size = new System.Drawing.Size(75, 34);
            this.btnPortOpen.TabIndex = 6;
            this.btnPortOpen.Text = "Port Open";
            this.btnPortOpen.UseVisualStyleBackColor = true;
            this.btnPortOpen.Click += new System.EventHandler(this.btnPortOpen_Click);
            // 
            // cbStopBits
            // 
            this.cbStopBits.FormattingEnabled = true;
            this.cbStopBits.Items.AddRange(new object[] {
            "None",
            "1",
            "1.5",
            "2"});
            this.cbStopBits.Location = new System.Drawing.Point(88, 172);
            this.cbStopBits.Name = "cbStopBits";
            this.cbStopBits.Size = new System.Drawing.Size(95, 20);
            this.cbStopBits.TabIndex = 5;
            this.cbStopBits.Text = "1";
            this.cbStopBits.SelectedIndexChanged += new System.EventHandler(this.cbStopBits_SelectedIndexChanged);
            // 
            // cbParity
            // 
            this.cbParity.FormattingEnabled = true;
            this.cbParity.Items.AddRange(new object[] {
            "Even",
            "Mark",
            "None",
            "Odd",
            "Space",
            "None"});
            this.cbParity.Location = new System.Drawing.Point(88, 135);
            this.cbParity.Name = "cbParity";
            this.cbParity.Size = new System.Drawing.Size(95, 20);
            this.cbParity.TabIndex = 5;
            this.cbParity.Text = "None";
            this.cbParity.SelectedIndexChanged += new System.EventHandler(this.cbParity_SelectedIndexChanged);
            // 
            // cbDataBits
            // 
            this.cbDataBits.FormattingEnabled = true;
            this.cbDataBits.Items.AddRange(new object[] {
            "8",
            "7"});
            this.cbDataBits.Location = new System.Drawing.Point(88, 98);
            this.cbDataBits.Name = "cbDataBits";
            this.cbDataBits.Size = new System.Drawing.Size(95, 20);
            this.cbDataBits.TabIndex = 5;
            this.cbDataBits.Text = "8";
            this.cbDataBits.SelectedIndexChanged += new System.EventHandler(this.cbDataBits_SelectedIndexChanged);
            // 
            // cbBaudRate
            // 
            this.cbBaudRate.FormattingEnabled = true;
            this.cbBaudRate.Items.AddRange(new object[] {
            "9600",
            "14400",
            "19200",
            "38400",
            "57600",
            "115200",
            "128000"});
            this.cbBaudRate.Location = new System.Drawing.Point(88, 61);
            this.cbBaudRate.Name = "cbBaudRate";
            this.cbBaudRate.Size = new System.Drawing.Size(95, 20);
            this.cbBaudRate.TabIndex = 5;
            this.cbBaudRate.Text = "115200";
            this.cbBaudRate.SelectedIndexChanged += new System.EventHandler(this.cbBaudRate_SelectedIndexChanged);
            // 
            // cbComPort
            // 
            this.cbComPort.FormattingEnabled = true;
            this.cbComPort.Location = new System.Drawing.Point(88, 24);
            this.cbComPort.Name = "cbComPort";
            this.cbComPort.Size = new System.Drawing.Size(95, 20);
            this.cbComPort.TabIndex = 5;
            this.cbComPort.SelectedIndexChanged += new System.EventHandler(this.cbComPort_SelectedIndexChanged);
            // 
            // lblStopBits
            // 
            this.lblStopBits.AutoSize = true;
            this.lblStopBits.Location = new System.Drawing.Point(16, 175);
            this.lblStopBits.Name = "lblStopBits";
            this.lblStopBits.Size = new System.Drawing.Size(55, 12);
            this.lblStopBits.TabIndex = 4;
            this.lblStopBits.Text = "Stop Bits";
            // 
            // lblDataBits
            // 
            this.lblDataBits.AutoSize = true;
            this.lblDataBits.Location = new System.Drawing.Point(16, 101);
            this.lblDataBits.Name = "lblDataBits";
            this.lblDataBits.Size = new System.Drawing.Size(51, 12);
            this.lblDataBits.TabIndex = 3;
            this.lblDataBits.Text = "DataBits";
            // 
            // lblParity
            // 
            this.lblParity.AutoSize = true;
            this.lblParity.Location = new System.Drawing.Point(16, 138);
            this.lblParity.Name = "lblParity";
            this.lblParity.Size = new System.Drawing.Size(37, 12);
            this.lblParity.TabIndex = 2;
            this.lblParity.Text = "Parity";
            // 
            // lblBaudRate
            // 
            this.lblBaudRate.AutoSize = true;
            this.lblBaudRate.Location = new System.Drawing.Point(16, 64);
            this.lblBaudRate.Name = "lblBaudRate";
            this.lblBaudRate.Size = new System.Drawing.Size(63, 12);
            this.lblBaudRate.TabIndex = 1;
            this.lblBaudRate.Text = "Baud Rate";
            // 
            // lblComPort
            // 
            this.lblComPort.AutoSize = true;
            this.lblComPort.Location = new System.Drawing.Point(16, 27);
            this.lblComPort.Name = "lblComPort";
            this.lblComPort.Size = new System.Drawing.Size(58, 12);
            this.lblComPort.TabIndex = 0;
            this.lblComPort.Text = "Com Port";
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsslblStatus});
            this.statusStrip1.Location = new System.Drawing.Point(0, 279);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(584, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // tsslblStatus
            // 
            this.tsslblStatus.Name = "tsslblStatus";
            this.tsslblStatus.Size = new System.Drawing.Size(39, 17);
            this.tsslblStatus.Text = "Ready";
            // 
            // gbDataSend
            // 
            this.gbDataSend.Controls.Add(this.label1);
            this.gbDataSend.Controls.Add(this.rbAsciiSend);
            this.gbDataSend.Controls.Add(this.rbHexSend);
            this.gbDataSend.Controls.Add(this.rbDecSend);
            this.gbDataSend.Controls.Add(this.btnDataSend);
            this.gbDataSend.Controls.Add(this.tbDataSend);
            this.gbDataSend.Location = new System.Drawing.Point(223, 13);
            this.gbDataSend.Name = "gbDataSend";
            this.gbDataSend.Size = new System.Drawing.Size(349, 90);
            this.gbDataSend.TabIndex = 2;
            this.gbDataSend.TabStop = false;
            this.gbDataSend.Text = "Data Send";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(247, 41);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(91, 12);
            this.label1.TabIndex = 5;
            this.label1.Text = "1 바이트만 송신";
            // 
            // rbAsciiSend
            // 
            this.rbAsciiSend.AutoSize = true;
            this.rbAsciiSend.Location = new System.Drawing.Point(171, 21);
            this.rbAsciiSend.Name = "rbAsciiSend";
            this.rbAsciiSend.Size = new System.Drawing.Size(54, 16);
            this.rbAsciiSend.TabIndex = 4;
            this.rbAsciiSend.Text = "ASCII";
            this.rbAsciiSend.UseVisualStyleBackColor = true;
            // 
            // rbHexSend
            // 
            this.rbHexSend.AutoSize = true;
            this.rbHexSend.Checked = true;
            this.rbHexSend.Location = new System.Drawing.Point(91, 21);
            this.rbHexSend.Name = "rbHexSend";
            this.rbHexSend.Size = new System.Drawing.Size(59, 16);
            this.rbHexSend.TabIndex = 3;
            this.rbHexSend.TabStop = true;
            this.rbHexSend.Text = "16진수";
            this.rbHexSend.UseVisualStyleBackColor = true;
            // 
            // rbDecSend
            // 
            this.rbDecSend.AutoSize = true;
            this.rbDecSend.Location = new System.Drawing.Point(17, 21);
            this.rbDecSend.Name = "rbDecSend";
            this.rbDecSend.Size = new System.Drawing.Size(59, 16);
            this.rbDecSend.TabIndex = 2;
            this.rbDecSend.Text = "10진수";
            this.rbDecSend.UseVisualStyleBackColor = true;
            // 
            // btnDataSend
            // 
            this.btnDataSend.Location = new System.Drawing.Point(138, 53);
            this.btnDataSend.Name = "btnDataSend";
            this.btnDataSend.Size = new System.Drawing.Size(87, 23);
            this.btnDataSend.TabIndex = 1;
            this.btnDataSend.Text = "Data Send";
            this.btnDataSend.UseVisualStyleBackColor = true;
            this.btnDataSend.Click += new System.EventHandler(this.btnDataSend_Click);
            // 
            // tbDataSend
            // 
            this.tbDataSend.Location = new System.Drawing.Point(17, 55);
            this.tbDataSend.Name = "tbDataSend";
            this.tbDataSend.Size = new System.Drawing.Size(104, 21);
            this.tbDataSend.TabIndex = 0;
            this.tbDataSend.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // gbDataRecv
            // 
            this.gbDataRecv.Controls.Add(this.btnClear);
            this.gbDataRecv.Controls.Add(this.tbDataRecv);
            this.gbDataRecv.Controls.Add(this.rbAsciiRecv);
            this.gbDataRecv.Controls.Add(this.rbHexRecv);
            this.gbDataRecv.Controls.Add(this.rbDecRecv);
            this.gbDataRecv.Location = new System.Drawing.Point(223, 114);
            this.gbDataRecv.Name = "gbDataRecv";
            this.gbDataRecv.Size = new System.Drawing.Size(349, 158);
            this.gbDataRecv.TabIndex = 3;
            this.gbDataRecv.TabStop = false;
            this.gbDataRecv.Text = "Data Recieve";
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(263, 116);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(75, 28);
            this.btnClear.TabIndex = 4;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // tbDataRecv
            // 
            this.tbDataRecv.Location = new System.Drawing.Point(17, 25);
            this.tbDataRecv.Multiline = true;
            this.tbDataRecv.Name = "tbDataRecv";
            this.tbDataRecv.Size = new System.Drawing.Size(233, 119);
            this.tbDataRecv.TabIndex = 3;
            // 
            // rbAsciiRecv
            // 
            this.rbAsciiRecv.AutoSize = true;
            this.rbAsciiRecv.Location = new System.Drawing.Point(263, 85);
            this.rbAsciiRecv.Name = "rbAsciiRecv";
            this.rbAsciiRecv.Size = new System.Drawing.Size(54, 16);
            this.rbAsciiRecv.TabIndex = 2;
            this.rbAsciiRecv.Text = "ASCII";
            this.rbAsciiRecv.UseVisualStyleBackColor = true;
            // 
            // rbHexRecv
            // 
            this.rbHexRecv.AutoSize = true;
            this.rbHexRecv.Checked = true;
            this.rbHexRecv.Location = new System.Drawing.Point(263, 55);
            this.rbHexRecv.Name = "rbHexRecv";
            this.rbHexRecv.Size = new System.Drawing.Size(59, 16);
            this.rbHexRecv.TabIndex = 1;
            this.rbHexRecv.TabStop = true;
            this.rbHexRecv.Text = "16진수";
            this.rbHexRecv.UseVisualStyleBackColor = true;
            // 
            // rbDecRecv
            // 
            this.rbDecRecv.AutoSize = true;
            this.rbDecRecv.Location = new System.Drawing.Point(263, 25);
            this.rbDecRecv.Name = "rbDecRecv";
            this.rbDecRecv.Size = new System.Drawing.Size(59, 16);
            this.rbDecRecv.TabIndex = 0;
            this.rbDecRecv.Text = "10진수";
            this.rbDecRecv.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 301);
            this.Controls.Add(this.gbDataRecv);
            this.Controls.Add(this.gbDataSend);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.gbSerialSetting);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Simple Serial Test Program v1.0";
            this.gbSerialSetting.ResumeLayout(false);
            this.gbSerialSetting.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.gbDataSend.ResumeLayout(false);
            this.gbDataSend.PerformLayout();
            this.gbDataRecv.ResumeLayout(false);
            this.gbDataRecv.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gbSerialSetting;
        private System.Windows.Forms.ComboBox cbStopBits;
        private System.Windows.Forms.ComboBox cbParity;
        private System.Windows.Forms.ComboBox cbDataBits;
        private System.Windows.Forms.ComboBox cbBaudRate;
        private System.Windows.Forms.ComboBox cbComPort;
        private System.Windows.Forms.Label lblStopBits;
        private System.Windows.Forms.Label lblDataBits;
        private System.Windows.Forms.Label lblParity;
        private System.Windows.Forms.Label lblBaudRate;
        private System.Windows.Forms.Label lblComPort;
        private System.Windows.Forms.Button btnPortClose;
        private System.Windows.Forms.Button btnPortOpen;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel tsslblStatus;
        private System.Windows.Forms.GroupBox gbDataSend;
        private System.Windows.Forms.Button btnDataSend;
        private System.Windows.Forms.TextBox tbDataSend;
        private System.Windows.Forms.GroupBox gbDataRecv;
        private System.Windows.Forms.RadioButton rbAsciiSend;
        private System.Windows.Forms.RadioButton rbHexSend;
        private System.Windows.Forms.RadioButton rbDecSend;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RadioButton rbAsciiRecv;
        private System.Windows.Forms.RadioButton rbHexRecv;
        private System.Windows.Forms.RadioButton rbDecRecv;
        private System.Windows.Forms.TextBox tbDataRecv;
        private System.Windows.Forms.Button btnClear;
    }
}

