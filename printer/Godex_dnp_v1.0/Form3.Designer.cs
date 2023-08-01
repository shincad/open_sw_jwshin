namespace Test_170205
{
    partial class Form3
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
            this.Grp_Setting = new System.Windows.Forms.GroupBox();
            this.Cbo_PaperType = new System.Windows.Forms.ComboBox();
            this.Num_LeftMargin = new System.Windows.Forms.NumericUpDown();
            this.Num_Dark = new System.Windows.Forms.NumericUpDown();
            this.Lbl_Dark = new System.Windows.Forms.Label();
            this.Num_Height = new System.Windows.Forms.NumericUpDown();
            this.Num_Width = new System.Windows.Forms.NumericUpDown();
            this.Lbl_Height = new System.Windows.Forms.Label();
            this.Lbl_Width = new System.Windows.Forms.Label();
            this.Num_GapFeed = new System.Windows.Forms.NumericUpDown();
            this.Lbl_GapFeed = new System.Windows.Forms.Label();
            this.Num_Speed = new System.Windows.Forms.NumericUpDown();
            this.Lbl_Speed = new System.Windows.Forms.Label();
            this.Lbl_PaperType = new System.Windows.Forms.Label();
            this.Num_TopMargin = new System.Windows.Forms.NumericUpDown();
            this.Lbl_TopMargin = new System.Windows.Forms.Label();
            this.Lbl_LeftMargin = new System.Windows.Forms.Label();
            this.Btn_SettingSave = new System.Windows.Forms.Button();
            this.Btn_SettingClose = new System.Windows.Forms.Button();
            this.Grp_Setting.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Num_LeftMargin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Dark)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Height)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Width)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_GapFeed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Speed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_TopMargin)).BeginInit();
            this.SuspendLayout();
            // 
            // Grp_Setting
            // 
            this.Grp_Setting.Controls.Add(this.Cbo_PaperType);
            this.Grp_Setting.Controls.Add(this.Num_LeftMargin);
            this.Grp_Setting.Controls.Add(this.Num_Dark);
            this.Grp_Setting.Controls.Add(this.Lbl_Dark);
            this.Grp_Setting.Controls.Add(this.Num_Height);
            this.Grp_Setting.Controls.Add(this.Num_Width);
            this.Grp_Setting.Controls.Add(this.Lbl_Height);
            this.Grp_Setting.Controls.Add(this.Lbl_Width);
            this.Grp_Setting.Controls.Add(this.Num_GapFeed);
            this.Grp_Setting.Controls.Add(this.Lbl_GapFeed);
            this.Grp_Setting.Controls.Add(this.Num_Speed);
            this.Grp_Setting.Controls.Add(this.Lbl_Speed);
            this.Grp_Setting.Controls.Add(this.Lbl_PaperType);
            this.Grp_Setting.Controls.Add(this.Num_TopMargin);
            this.Grp_Setting.Controls.Add(this.Lbl_TopMargin);
            this.Grp_Setting.Controls.Add(this.Lbl_LeftMargin);
            this.Grp_Setting.Location = new System.Drawing.Point(23, 43);
            this.Grp_Setting.Name = "Grp_Setting";
            this.Grp_Setting.Size = new System.Drawing.Size(584, 225);
            this.Grp_Setting.TabIndex = 0;
            this.Grp_Setting.TabStop = false;
            this.Grp_Setting.Text = "인쇄설정";
            // 
            // Cbo_PaperType
            // 
            this.Cbo_PaperType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.Cbo_PaperType.FormattingEnabled = true;
            this.Cbo_PaperType.Items.AddRange(new object[] {
            "Gap",
            "Continue"});
            this.Cbo_PaperType.Location = new System.Drawing.Point(130, 116);
            this.Cbo_PaperType.Name = "Cbo_PaperType";
            this.Cbo_PaperType.Size = new System.Drawing.Size(90, 20);
            this.Cbo_PaperType.TabIndex = 16;
            // 
            // Num_LeftMargin
            // 
            this.Num_LeftMargin.Location = new System.Drawing.Point(130, 39);
            this.Num_LeftMargin.Maximum = new decimal(new int[] {
            49,
            0,
            0,
            0});
            this.Num_LeftMargin.Name = "Num_LeftMargin";
            this.Num_LeftMargin.Size = new System.Drawing.Size(89, 21);
            this.Num_LeftMargin.TabIndex = 15;
            // 
            // Num_Dark
            // 
            this.Num_Dark.Location = new System.Drawing.Point(400, 162);
            this.Num_Dark.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.Num_Dark.Name = "Num_Dark";
            this.Num_Dark.Size = new System.Drawing.Size(89, 21);
            this.Num_Dark.TabIndex = 14;
            // 
            // Lbl_Dark
            // 
            this.Lbl_Dark.AutoSize = true;
            this.Lbl_Dark.Location = new System.Drawing.Point(271, 164);
            this.Lbl_Dark.Name = "Lbl_Dark";
            this.Lbl_Dark.Size = new System.Drawing.Size(29, 12);
            this.Lbl_Dark.TabIndex = 13;
            this.Lbl_Dark.Text = "농도";
            // 
            // Num_Height
            // 
            this.Num_Height.Location = new System.Drawing.Point(400, 119);
            this.Num_Height.Name = "Num_Height";
            this.Num_Height.Size = new System.Drawing.Size(89, 21);
            this.Num_Height.TabIndex = 12;
            // 
            // Num_Width
            // 
            this.Num_Width.Location = new System.Drawing.Point(400, 74);
            this.Num_Width.Name = "Num_Width";
            this.Num_Width.Size = new System.Drawing.Size(89, 21);
            this.Num_Width.TabIndex = 11;
            // 
            // Lbl_Height
            // 
            this.Lbl_Height.AutoSize = true;
            this.Lbl_Height.Location = new System.Drawing.Point(271, 119);
            this.Lbl_Height.Name = "Lbl_Height";
            this.Lbl_Height.Size = new System.Drawing.Size(85, 12);
            this.Lbl_Height.TabIndex = 10;
            this.Lbl_Height.Text = "라벨높이(mm)";
            // 
            // Lbl_Width
            // 
            this.Lbl_Width.AutoSize = true;
            this.Lbl_Width.Location = new System.Drawing.Point(271, 76);
            this.Lbl_Width.Name = "Lbl_Width";
            this.Lbl_Width.Size = new System.Drawing.Size(85, 12);
            this.Lbl_Width.TabIndex = 9;
            this.Lbl_Width.Text = "라벨넓이(mm)";
            // 
            // Num_GapFeed
            // 
            this.Num_GapFeed.Location = new System.Drawing.Point(400, 37);
            this.Num_GapFeed.Name = "Num_GapFeed";
            this.Num_GapFeed.Size = new System.Drawing.Size(89, 21);
            this.Num_GapFeed.TabIndex = 8;
            // 
            // Lbl_GapFeed
            // 
            this.Lbl_GapFeed.AutoSize = true;
            this.Lbl_GapFeed.Location = new System.Drawing.Point(271, 41);
            this.Lbl_GapFeed.Name = "Lbl_GapFeed";
            this.Lbl_GapFeed.Size = new System.Drawing.Size(109, 12);
            this.Lbl_GapFeed.TabIndex = 7;
            this.Lbl_GapFeed.Text = "라벨사이간격(mm)";
            // 
            // Num_Speed
            // 
            this.Num_Speed.Location = new System.Drawing.Point(130, 162);
            this.Num_Speed.Maximum = new decimal(new int[] {
            7,
            0,
            0,
            0});
            this.Num_Speed.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.Num_Speed.Name = "Num_Speed";
            this.Num_Speed.Size = new System.Drawing.Size(89, 21);
            this.Num_Speed.TabIndex = 6;
            this.Num_Speed.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            // 
            // Lbl_Speed
            // 
            this.Lbl_Speed.AutoSize = true;
            this.Lbl_Speed.Location = new System.Drawing.Point(22, 164);
            this.Lbl_Speed.Name = "Lbl_Speed";
            this.Lbl_Speed.Size = new System.Drawing.Size(80, 12);
            this.Lbl_Speed.TabIndex = 5;
            this.Lbl_Speed.Text = "인쇄속도(ips)";
            // 
            // Lbl_PaperType
            // 
            this.Lbl_PaperType.AutoSize = true;
            this.Lbl_PaperType.Location = new System.Drawing.Point(22, 119);
            this.Lbl_PaperType.Name = "Lbl_PaperType";
            this.Lbl_PaperType.Size = new System.Drawing.Size(53, 12);
            this.Lbl_PaperType.TabIndex = 4;
            this.Lbl_PaperType.Text = "용지종류";
            // 
            // Num_TopMargin
            // 
            this.Num_TopMargin.Location = new System.Drawing.Point(130, 74);
            this.Num_TopMargin.Name = "Num_TopMargin";
            this.Num_TopMargin.Size = new System.Drawing.Size(89, 21);
            this.Num_TopMargin.TabIndex = 3;
            // 
            // Lbl_TopMargin
            // 
            this.Lbl_TopMargin.AutoSize = true;
            this.Lbl_TopMargin.Location = new System.Drawing.Point(22, 76);
            this.Lbl_TopMargin.Name = "Lbl_TopMargin";
            this.Lbl_TopMargin.Size = new System.Drawing.Size(89, 12);
            this.Lbl_TopMargin.TabIndex = 2;
            this.Lbl_TopMargin.Text = "상측여백 (mm)";
            // 
            // Lbl_LeftMargin
            // 
            this.Lbl_LeftMargin.AutoSize = true;
            this.Lbl_LeftMargin.Location = new System.Drawing.Point(22, 41);
            this.Lbl_LeftMargin.Name = "Lbl_LeftMargin";
            this.Lbl_LeftMargin.Size = new System.Drawing.Size(89, 12);
            this.Lbl_LeftMargin.TabIndex = 0;
            this.Lbl_LeftMargin.Text = "왼쪽여백 (mm)";
            // 
            // Btn_SettingSave
            // 
            this.Btn_SettingSave.Location = new System.Drawing.Point(338, 285);
            this.Btn_SettingSave.Name = "Btn_SettingSave";
            this.Btn_SettingSave.Size = new System.Drawing.Size(108, 32);
            this.Btn_SettingSave.TabIndex = 1;
            this.Btn_SettingSave.Text = "저장";
            this.Btn_SettingSave.UseVisualStyleBackColor = true;
            this.Btn_SettingSave.Click += new System.EventHandler(this.Btn_SettingSave_Click);
            // 
            // Btn_SettingClose
            // 
            this.Btn_SettingClose.Location = new System.Drawing.Point(485, 285);
            this.Btn_SettingClose.Name = "Btn_SettingClose";
            this.Btn_SettingClose.Size = new System.Drawing.Size(108, 32);
            this.Btn_SettingClose.TabIndex = 2;
            this.Btn_SettingClose.Text = "닫기";
            this.Btn_SettingClose.UseVisualStyleBackColor = true;
            this.Btn_SettingClose.Click += new System.EventHandler(this.Btn_SettingClose_Click);
            // 
            // Form3
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(671, 329);
            this.Controls.Add(this.Btn_SettingClose);
            this.Controls.Add(this.Btn_SettingSave);
            this.Controls.Add(this.Grp_Setting);
            this.Name = "Form3";
            this.Text = "설정";
            this.Load += new System.EventHandler(this.Form3_Load);
            this.Grp_Setting.ResumeLayout(false);
            this.Grp_Setting.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Num_LeftMargin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Dark)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Height)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Width)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_GapFeed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Speed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_TopMargin)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox Grp_Setting;
        private System.Windows.Forms.Label Lbl_LeftMargin;
        private System.Windows.Forms.NumericUpDown Num_Dark;
        private System.Windows.Forms.Label Lbl_Dark;
        private System.Windows.Forms.NumericUpDown Num_Height;
        private System.Windows.Forms.NumericUpDown Num_Width;
        private System.Windows.Forms.Label Lbl_Height;
        private System.Windows.Forms.Label Lbl_Width;
        private System.Windows.Forms.NumericUpDown Num_GapFeed;
        private System.Windows.Forms.Label Lbl_GapFeed;
        private System.Windows.Forms.NumericUpDown Num_Speed;
        private System.Windows.Forms.Label Lbl_Speed;
        private System.Windows.Forms.Label Lbl_PaperType;
        private System.Windows.Forms.NumericUpDown Num_TopMargin;
        private System.Windows.Forms.Label Lbl_TopMargin;
        private System.Windows.Forms.Button Btn_SettingSave;
        private System.Windows.Forms.Button Btn_SettingClose;
        private System.Windows.Forms.NumericUpDown Num_LeftMargin;
        private System.Windows.Forms.ComboBox Cbo_PaperType;
    }
}