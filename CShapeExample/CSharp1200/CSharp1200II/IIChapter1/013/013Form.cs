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

namespace CSharp1200.CSharp1200II.IIChapter1._013
{
    public partial class _013Form : Form
    {
        public _013Form()
        {
            InitializeComponent();
        }

        MouseHook mouseHook = new MouseHook();
        #region 设置系统热键用到的声明
        [DllImport("user32.dll", SetLastError = true)]
        public static extern bool RegisterHotKey(IntPtr Hwnd, int Id, KeyModifiers keyModifiers, Keys key);

        [DllImport("user32.dll", SetLastError = true)]
        public static extern bool UnregisterHotKey(IntPtr Hwnd, int Id);

        [Flags()]
        public enum KeyModifiers
        {
            None = 0,
            Alt = 1,
            Control = 2,
        }
        #endregion

        //标识屏蔽条件
        public static bool flagL = false;
        public static bool flagR = false;
        public static bool flagM = false;
        private void button1_Click(object sender, EventArgs e)
        {
            mouseHook.StartHook();

            flagL = checkBox1.Checked;
            flagM = checkBox2.Checked;
            flagR = checkBox3.Checked;

            mouseHook.StartHook();
            //调用钩子后获取鼠标的按下事件
            mouseHook.MouseDown += new MouseEventHandler(Mouse_Down);
        }

        #region 传递鼠标事件的函数
        void Mouse_Down(object sender, MouseEventArgs e)
        {

        }

        public void AddMouseValueEvent(string MouseValue)
        {
            MessageBox.Show(MouseValue);
        }
        #endregion

        #region 设置系统热键
        private void Form1_Load(object sender, EventArgs e)
        {
            Clipboard.Clear();
            RegisterHotKey(Handle, 100, 0, Keys.F10);
            flagL = false;
            flagR = false;
            flagM = false;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            UnregisterHotKey(Handle, 100);
        }

        protected override void WndProc(ref Message m)
        {
            const int WM_Key = 0x312;
            switch (m.Msg)
            {
                case WM_Key:
                    #region 释放钩子
                    mouseHook.UnInstallHook();
                    #endregion
                    break;
            }
            base.WndProc(ref m);
        }
        #endregion
    }
}
