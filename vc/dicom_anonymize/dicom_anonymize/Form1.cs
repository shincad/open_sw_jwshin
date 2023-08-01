using FellowOakDicom;
using System;
using System.IO;
using System.Windows.Forms;


namespace dicom_anonymize
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        // 파일 갯수 카운트 변수
        int count = 0;
        // 파일 존재 유무 Flag
        Boolean ExistFlag;

        private void button1_Click_1(object sender, EventArgs e)
        {
            // 파일 존재 유무 Flag 초기화
            ExistFlag = false;
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.Description = "Select DICOM directory";
            fbd.ShowNewFolderButton = false;

            if (fbd.ShowDialog() == DialogResult.OK)
            {
                string dcmDir = fbd.SelectedPath;
                textBox1.Text = dcmDir;

                // 저장 폴더 지정
                string outDir = @"c:\dicom_test\anon";
                textBox2.Text = "";
                // 저장 폴더 없을 경우 생성
                if (!Directory.Exists(outDir))
                {
                    Directory.CreateDirectory(outDir);
                }
                // dcm 파일 찾아서 익명화 처리
                foreach (string dcmFile in Directory.GetFiles(dcmDir))
                {
                    if (Path.GetExtension(dcmFile).ToLower() == ".dcm")
                    {
                        string outPath = Path.Combine(outDir, Path.GetFileName(dcmFile));
                        var ds = DicomFile.Open(dcmFile);
                        ds.Dataset.AddOrUpdate(DicomTag.PatientName, "anonymous");
                        ds.Dataset.AddOrUpdate(DicomTag.PatientID, "anonymous");
                        ds.Save(outPath);
                        // 파일갯수 카운트
                        count++;
                        textBox2.Text = count.ToString();
                        // 파일 존재 Flag Set
                        ExistFlag = true;
                    }

                }
                if (ExistFlag == true)
                {
                    MessageBox.Show("dcm 익명화 완료");
                }
                else
                {
                    MessageBox.Show("dcm 파일이 없습니다.");
                    ExistFlag = false;
                }
            }
        }
    }
}
