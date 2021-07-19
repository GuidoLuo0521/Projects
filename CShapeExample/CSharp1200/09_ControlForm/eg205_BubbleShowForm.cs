using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._09_ControlForm
{
    public partial class eg205_BubbleShowForm : Form
    {
        public eg205_BubbleShowForm()
        {
            InitializeComponent();
            this.notifyIcon1.Icon = Resources.front;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.notifyIcon1.Visible = true;
            this.notifyIcon1.ShowBalloonTip(1000, "当前时间", DateTime.Now.ToString(), ToolTipIcon.Info);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.notifyIcon1.Visible = false;
        }

        /////////////////////////////////////////////////////////////////////////////
        /// 右下角提示窗口  
        [DllImport("user32.dll")]
        private static extern bool AnimateWindow(IntPtr handle, int dwTime, int dwFlag);


        private void ShowPopup(bool bShow)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            
        }

        private void button4_Click(object sender, EventArgs e)
        {

        }
    }
}
