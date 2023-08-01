namespace Test_170205
{
    partial class Frm_PrinterSetting
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
            this.Btn_PortSave = new System.Windows.Forms.Button();
            this.Btn_Close = new System.Windows.Forms.Button();
            this.Grp_Port = new System.Windows.Forms.GroupBox();
            this.RBtn_Drv = new System.Windows.Forms.RadioButton();
            this.RBtn_USB = new System.Windows.Forms.RadioButton();
            this.Cbo_Drv = new System.Windows.Forms.ComboBox();
            this.Grp_Port.SuspendLayout();
            this.SuspendLayout();
            // 
            // Btn_PortSave
            // 
            this.Btn_PortSave.Location = new System.Drawing.Point(17, 145);
            this.Btn_PortSave.Name = "Btn_PortSave";
            this.Btn_PortSave.Size = new System.Drawing.Size(89, 22);
            this.Btn_PortSave.TabIndex = 3;
            this.Btn_PortSave.Text = "저장";
            this.Btn_PortSave.UseVisualStyleBackColor = true;
            this.Btn_PortSave.Click += new System.EventHandler(this.Btn_PortSave_Click);
            // 
            // Btn_Close
            // 
            this.Btn_Close.Location = new System.Drawing.Point(142, 145);
            this.Btn_Close.Name = "Btn_Close";
            this.Btn_Close.Size = new System.Drawing.Size(89, 22);
            this.Btn_Close.TabIndex = 4;
            this.Btn_Close.Text = "닫기";
            this.Btn_Close.UseVisualStyleBackColor = true;
            this.Btn_Close.Click += new System.EventHandler(this.Btn_Close_Click);
            // 
            // Grp_Port
            // 
            this.Grp_Port.Controls.Add(this.Cbo_Drv);
            this.Grp_Port.Controls.Add(this.RBtn_Drv);
            this.Grp_Port.Controls.Add(this.RBtn_USB);
            this.Grp_Port.Location = new System.Drawing.Point(30, 30);
            this.Grp_Port.Name = "Grp_Port";
            this.Grp_Port.Size = new System.Drawing.Size(286, 88);
            this.Grp_Port.TabIndex = 5;
            this.Grp_Port.TabStop = false;
            this.Grp_Port.Text = "포트";
            // 
            // RBtn_Drv
            // 
            this.RBtn_Drv.AutoSize = true;
            this.RBtn_Drv.Location = new System.Drawing.Point(24, 50);
            this.RBtn_Drv.Name = "RBtn_Drv";
            this.RBtn_Drv.Size = new System.Drawing.Size(83, 16);
            this.RBtn_Drv.TabIndex = 1;
            this.RBtn_Drv.TabStop = true;
            this.RBtn_Drv.Text = "Driver 선택";
            this.RBtn_Drv.UseVisualStyleBackColor = true;
            // 
            // RBtn_USB
            // 
            this.RBtn_USB.AutoSize = true;
            this.RBtn_USB.Location = new System.Drawing.Point(24, 28);
            this.RBtn_USB.Name = "RBtn_USB";
            this.RBtn_USB.Size = new System.Drawing.Size(47, 16);
            this.RBtn_USB.TabIndex = 0;
            this.RBtn_USB.TabStop = true;
            this.RBtn_USB.Text = "USB";
            this.RBtn_USB.UseVisualStyleBackColor = true;
            // 
            // Cbo_Drv
            // 
            this.Cbo_Drv.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.Cbo_Drv.FormattingEnabled = true;
            this.Cbo_Drv.Location = new System.Drawing.Point(122, 49);
            this.Cbo_Drv.Name = "Cbo_Drv";
            this.Cbo_Drv.Size = new System.Drawing.Size(135, 20);
            this.Cbo_Drv.TabIndex = 2;
            this.Cbo_Drv.SelectedIndexChanged += new System.EventHandler(this.Cbo_Drv_SelectedIndexChanged);
            // 
            // Frm_PrinterSetting
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(354, 179);
            this.Controls.Add(this.Grp_Port);
            this.Controls.Add(this.Btn_Close);
            this.Controls.Add(this.Btn_PortSave);
            this.Name = "Frm_PrinterSetting";
            this.Text = "프린터설정";
            this.Load += new System.EventHandler(this.Frm_PrinterSetting_Load);
            this.Grp_Port.ResumeLayout(false);
            this.Grp_Port.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button Btn_PortSave;
        private System.Windows.Forms.Button Btn_Close;
        private System.Windows.Forms.GroupBox Grp_Port;
        private System.Windows.Forms.RadioButton RBtn_Drv;
        private System.Windows.Forms.RadioButton RBtn_USB;
        private System.Windows.Forms.ComboBox Cbo_Drv;
    }
}