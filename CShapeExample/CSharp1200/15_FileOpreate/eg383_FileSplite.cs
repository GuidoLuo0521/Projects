using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._15_FileOpreate
{
    public partial class eg383_FileSplite : Form
    {
        public eg383_FileSplite()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            if(fileDialog.ShowDialog() == DialogResult.OK)
            {

                FileStream splitFileStream = new FileStream(fileDialog.FileName, FileMode.Open);
                BinaryReader splitBinReader = new BinaryReader(splitFileStream);

                int nFileSize = 10 * 1024 * 1024;
                byte[] tempBytes;
                int nFileCount = (int)(splitFileStream.Length / nFileSize);
                if (splitFileStream.Length % nFileSize != 0)
                    ++nFileCount;

                string[] strExtra = fileDialog.FileName.Split('.');
                for (int i = 0; i < nFileCount; ++i) 
                {
                    // 
                    string strSplitFileName = Path.GetDirectoryName(fileDialog.FileName) +
                        $"\\{Path.GetFileNameWithoutExtension(fileDialog.FileName)}-{i.ToString().PadLeft(4, '0')}.{strExtra[strExtra.Length - 1]}";
                    this.richTextBox1.AppendText(strSplitFileName + Environment.NewLine);

                    FileStream tempStream = new FileStream(strSplitFileName, FileMode.OpenOrCreate);
                    BinaryWriter tempWriter = new BinaryWriter(tempStream);

                    tempBytes = splitBinReader.ReadBytes(nFileSize);
                    tempWriter.Write(tempBytes);
                    tempWriter.Close();
                    tempStream.Close();
                }

                splitFileStream.Close();
                splitBinReader.Close();
                MessageBox.Show("分割成功~");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // Directory
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.richTextBox1.Text = Application.StartupPath;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            this.richTextBox1.Text = "";
            char[] arr = Path.GetInvalidFileNameChars();
            foreach(char item in arr)
            {
                this.richTextBox1.AppendText(item.ToString() + "  ");
            }
        }
    }
}
