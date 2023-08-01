namespace Test_170205
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.mmMainMenu = new System.Windows.Forms.MenuStrip();
            this.mnuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.miBarcode_Print = new System.Windows.Forms.ToolStripMenuItem();
            this.miExit = new System.Windows.Forms.ToolStripMenuItem();
            this.옵션OToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.miSetting = new System.Windows.Forms.ToolStripMenuItem();
            this.miPrinterSetting = new System.Windows.Forms.ToolStripMenuItem();
            this.Grp_LabelType = new System.Windows.Forms.GroupBox();
            this.Cbo_Large = new System.Windows.Forms.RadioButton();
            this.Cbo_Small = new System.Windows.Forms.RadioButton();
            this.Lbl_Page = new System.Windows.Forms.Label();
            this.Lbl_Copy = new System.Windows.Forms.Label();
            this.Num_Page = new System.Windows.Forms.NumericUpDown();
            this.Num_Copy = new System.Windows.Forms.NumericUpDown();
            this.Lbl_Barcode = new System.Windows.Forms.Label();
            this.Txt_Barcode = new System.Windows.Forms.TextBox();
            this.Btn_PrintBarcode = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.mmMainMenu.SuspendLayout();
            this.Grp_LabelType.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Page)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Copy)).BeginInit();
            this.SuspendLayout();
            // 
            // mmMainMenu
            // 
            this.mmMainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFile,
            this.옵션OToolStripMenuItem});
            this.mmMainMenu.Location = new System.Drawing.Point(0, 0);
            this.mmMainMenu.Name = "mmMainMenu";
            this.mmMainMenu.Size = new System.Drawing.Size(539, 24);
            this.mmMainMenu.TabIndex = 0;
            this.mmMainMenu.Text = "menuStrip1";
            // 
            // mnuFile
            // 
            this.mnuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miBarcode_Print,
            this.miExit});
            this.mnuFile.Name = "mnuFile";
            this.mnuFile.Size = new System.Drawing.Size(57, 20);
            this.mnuFile.Text = "파일(&F)";
            // 
            // miBarcode_Print
            // 
            this.miBarcode_Print.Name = "miBarcode_Print";
            this.miBarcode_Print.Size = new System.Drawing.Size(152, 22);
            this.miBarcode_Print.Text = "바코드인쇄";
            this.miBarcode_Print.Click += new System.EventHandler(this.Btn_PrintBarcode_Click);
            // 
            // miExit
            // 
            this.miExit.Name = "miExit";
            this.miExit.Size = new System.Drawing.Size(152, 22);
            this.miExit.Text = "나가기(Ctrl+x)";
            this.miExit.Click += new System.EventHandler(this.miExit_Click);
            // 
            // 옵션OToolStripMenuItem
            // 
            this.옵션OToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miSetting,
            this.miPrinterSetting});
            this.옵션OToolStripMenuItem.Name = "옵션OToolStripMenuItem";
            this.옵션OToolStripMenuItem.Size = new System.Drawing.Size(60, 20);
            this.옵션OToolStripMenuItem.Text = "옵션(&O)";
            // 
            // miSetting
            // 
            this.miSetting.Name = "miSetting";
            this.miSetting.Size = new System.Drawing.Size(134, 22);
            this.miSetting.Text = "설정";
            this.miSetting.Click += new System.EventHandler(this.miSetting_Click);
            // 
            // miPrinterSetting
            // 
            this.miPrinterSetting.Name = "miPrinterSetting";
            this.miPrinterSetting.Size = new System.Drawing.Size(134, 22);
            this.miPrinterSetting.Text = "프린터설정";
            this.miPrinterSetting.Click += new System.EventHandler(this.miPrinterSetting_Click);
            // 
            // Grp_LabelType
            // 
            this.Grp_LabelType.Controls.Add(this.Cbo_Large);
            this.Grp_LabelType.Controls.Add(this.Cbo_Small);
            this.Grp_LabelType.Location = new System.Drawing.Point(25, 84);
            this.Grp_LabelType.Name = "Grp_LabelType";
            this.Grp_LabelType.Size = new System.Drawing.Size(164, 106);
            this.Grp_LabelType.TabIndex = 1;
            this.Grp_LabelType.TabStop = false;
            this.Grp_LabelType.Text = "라벨종류";
            // 
            // Cbo_Large
            // 
            this.Cbo_Large.AutoSize = true;
            this.Cbo_Large.Location = new System.Drawing.Point(19, 61);
            this.Cbo_Large.Name = "Cbo_Large";
            this.Cbo_Large.Size = new System.Drawing.Size(124, 18);
            this.Cbo_Large.TabIndex = 1;
            this.Cbo_Large.TabStop = true;
            this.Cbo_Large.Text = "통합바코드(18자리)";
            this.Cbo_Large.UseVisualStyleBackColor = true;
            this.Cbo_Large.CheckedChanged += new System.EventHandler(this.Cbo_Large_CheckedChanged);
            // 
            // Cbo_Small
            // 
            this.Cbo_Small.AutoSize = true;
            this.Cbo_Small.Location = new System.Drawing.Point(19, 35);
            this.Cbo_Small.Name = "Cbo_Small";
            this.Cbo_Small.Size = new System.Drawing.Size(124, 18);
            this.Cbo_Small.TabIndex = 0;
            this.Cbo_Small.TabStop = true;
            this.Cbo_Small.Text = "일반바코드(12자리)";
            this.Cbo_Small.UseVisualStyleBackColor = true;
            this.Cbo_Small.CheckedChanged += new System.EventHandler(this.Cbo_Small_CheckedChanged);
            // 
            // Lbl_Page
            // 
            this.Lbl_Page.AutoSize = true;
            this.Lbl_Page.Location = new System.Drawing.Point(26, 267);
            this.Lbl_Page.Name = "Lbl_Page";
            this.Lbl_Page.Size = new System.Drawing.Size(51, 14);
            this.Lbl_Page.TabIndex = 2;
            this.Lbl_Page.Text = "발행수량";
            // 
            // Lbl_Copy
            // 
            this.Lbl_Copy.AutoSize = true;
            this.Lbl_Copy.Location = new System.Drawing.Point(26, 303);
            this.Lbl_Copy.Name = "Lbl_Copy";
            this.Lbl_Copy.Size = new System.Drawing.Size(51, 14);
            this.Lbl_Copy.TabIndex = 3;
            this.Lbl_Copy.Text = "사본수량";
            // 
            // Num_Page
            // 
            this.Num_Page.Location = new System.Drawing.Point(85, 262);
            this.Num_Page.Name = "Num_Page";
            this.Num_Page.Size = new System.Drawing.Size(125, 21);
            this.Num_Page.TabIndex = 4;
            this.Num_Page.ValueChanged += new System.EventHandler(this.Num_Page_ValueChanged);
            // 
            // Num_Copy
            // 
            this.Num_Copy.Location = new System.Drawing.Point(85, 301);
            this.Num_Copy.Name = "Num_Copy";
            this.Num_Copy.Size = new System.Drawing.Size(125, 21);
            this.Num_Copy.TabIndex = 5;
            this.Num_Copy.ValueChanged += new System.EventHandler(this.Num_Copy_ValueChanged);
            // 
            // Lbl_Barcode
            // 
            this.Lbl_Barcode.AutoSize = true;
            this.Lbl_Barcode.Location = new System.Drawing.Point(244, 267);
            this.Lbl_Barcode.Name = "Lbl_Barcode";
            this.Lbl_Barcode.Size = new System.Drawing.Size(40, 14);
            this.Lbl_Barcode.TabIndex = 6;
            this.Lbl_Barcode.Text = "바코드";
            // 
            // Txt_Barcode
            // 
            this.Txt_Barcode.Location = new System.Drawing.Point(303, 262);
            this.Txt_Barcode.Name = "Txt_Barcode";
            this.Txt_Barcode.Size = new System.Drawing.Size(165, 21);
            this.Txt_Barcode.TabIndex = 7;
            // 
            // Btn_PrintBarcode
            // 
            this.Btn_PrintBarcode.Location = new System.Drawing.Point(28, 385);
            this.Btn_PrintBarcode.Name = "Btn_PrintBarcode";
            this.Btn_PrintBarcode.Size = new System.Drawing.Size(163, 33);
            this.Btn_PrintBarcode.TabIndex = 8;
            this.Btn_PrintBarcode.Text = "바코드인쇄";
            this.Btn_PrintBarcode.UseVisualStyleBackColor = true;
            this.Btn_PrintBarcode.Click += new System.EventHandler(this.Btn_PrintBarcode_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(249, 404);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(271, 14);
            this.label1.TabIndex = 21;
            this.label1.Text = "Copyright(c)2017 Dnpsystem All rights reserved.";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(539, 432);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Btn_PrintBarcode);
            this.Controls.Add(this.Txt_Barcode);
            this.Controls.Add(this.Lbl_Barcode);
            this.Controls.Add(this.Num_Copy);
            this.Controls.Add(this.Num_Page);
            this.Controls.Add(this.Lbl_Copy);
            this.Controls.Add(this.Lbl_Page);
            this.Controls.Add(this.Grp_LabelType);
            this.Controls.Add(this.mmMainMenu);
            this.Font = new System.Drawing.Font("나눔고딕", 8.999999F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.Name = "Form1";
            this.Text = "도서관용 바코드 프로그램 (Godex) ";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.mmMainMenu.ResumeLayout(false);
            this.mmMainMenu.PerformLayout();
            this.Grp_LabelType.ResumeLayout(false);
            this.Grp_LabelType.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Page)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Num_Copy)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip mmMainMenu;
        private System.Windows.Forms.ToolStripMenuItem mnuFile;
        private System.Windows.Forms.ToolStripMenuItem miBarcode_Print;
        private System.Windows.Forms.ToolStripMenuItem miExit;
        private System.Windows.Forms.ToolStripMenuItem 옵션OToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem miSetting;
        private System.Windows.Forms.ToolStripMenuItem miPrinterSetting;
        private System.Windows.Forms.GroupBox Grp_LabelType;
        private System.Windows.Forms.RadioButton Cbo_Large;
        private System.Windows.Forms.RadioButton Cbo_Small;
        private System.Windows.Forms.Label Lbl_Page;
        private System.Windows.Forms.Label Lbl_Copy;
        private System.Windows.Forms.NumericUpDown Num_Page;
        private System.Windows.Forms.NumericUpDown Num_Copy;
        private System.Windows.Forms.Label Lbl_Barcode;
        private System.Windows.Forms.TextBox Txt_Barcode;
        private System.Windows.Forms.Button Btn_PrintBarcode;
        private System.Windows.Forms.Label label1;
    }
}

