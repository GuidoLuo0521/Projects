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
    public partial class eg400_FileOpreater : Form
    {
        public eg400_FileOpreater()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 保存uttf8格式文件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSaveFile_Click(object sender, EventArgs e)
        {
            SaveFileDialog fileDialog = new SaveFileDialog();
            fileDialog.InitialDirectory = Application.StartupPath;
            if(fileDialog.ShowDialog() == DialogResult.OK)
            {
                // 使用using 关键字，自动释放资源 
                // 创建 IDisposable接口的类，using 结束后，程序自动调用IDisposable的Dispose方法。
                using (StreamWriter writer = new StreamWriter(fileDialog.FileName, true))
                {
                    writer.Write(this.richTextBox1.Text);
                    writer.Close();
                }
            }
        }

        private void btnOpenFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.InitialDirectory = Application.StartupPath;
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                using (StreamReader reader = new StreamReader(fileDialog.FileName, true)) 
                {
                    this.richTextBox1.Text = reader.ReadToEnd();
                    reader.Close();
                }
            }
        }

        private void btSaveWebFile_Click(object sender, EventArgs e)
        {
            SaveFileDialog fileDialog = new SaveFileDialog();
            fileDialog.InitialDirectory = Application.StartupPath;
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                // 使用using 关键字，自动释放资源 
                // 创建 IDisposable接口的类，using 结束后，程序自动调用IDisposable的Dispose方法。
                string strHtml = Path.GetFileNameWithoutExtension(fileDialog.FileName) + ".html";
                using (StreamWriter writer = new StreamWriter(fileDialog.FileName, true))
                {
                    writer.Write("<p>");
                    writer.Write(this.richTextBox1.Text);
                    writer.Write("</p>");
                    writer.Close();
                }

                // System.Diagnostics 命名空间:提供允许你与系统进程、事件日志和性能计数器进行交互的类。
                System.Diagnostics.Process.Start(strHtml);
            }
        }
    }
}
