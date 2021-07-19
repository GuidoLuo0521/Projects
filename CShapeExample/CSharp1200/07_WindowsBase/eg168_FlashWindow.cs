using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._07_WindowsBase
{

    public partial class eg168_FlashWindow : Form
    {

        [System.Runtime.InteropServices.DllImport("user32.dll")]
        public static extern bool FlashWindow(IntPtr handle, bool bInvert);

/*        bool _bFlashWindow = false;*/
        public eg168_FlashWindow()
        {
            InitializeComponent();

            this.timer1.Interval = 700;
            this.timer1.Tick += Timer1_Tick;
        }

        private void Timer1_Tick(object sender, EventArgs e)
        {
//             if(_bFlashWindow)
//             {
//                 FlashWindow(this.Handle, true);
//             }

            FlashWindow(this.Handle, true);
        }

        private void button1_Click(object sender, EventArgs e)
        {
//             _bFlashWindow = true;
//             this.timer1.Start();

            this.timer1.Enabled = true;

        }

        private void button2_Click(object sender, EventArgs e)
        {
//             _bFlashWindow = false;
//             this.timer1.Stop();

            this.timer1.Enabled = false;
        }
    }
}
