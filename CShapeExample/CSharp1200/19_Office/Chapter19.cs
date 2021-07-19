using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._19_Office
{
    public partial class Chapter19 : Form
    {
        public Chapter19()
        {
            InitializeComponent();
        }

        private void btnWebBrowser_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.InitialDirectory = Application.StartupPath;
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                this.webBrowser1.Navigate(fileDialog.FileName);
            }
        }

        private void btnCreateWord_Click(object sender, EventArgs e)
        {
            SaveFileDialog fileDialog = new SaveFileDialog();
            fileDialog.InitialDirectory = Application.StartupPath;
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                ThreadPool.QueueUserWorkItem((pp) =>
                {
                    
                });
            }
        }
    }
}
