using CSharp1200.CSharp1200II.IIChapter1._013;
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

namespace CSharp1200.CSharp1200II
{
    public partial class _1200II_Chapter1 : Form
    {
        public _1200II_Chapter1()
        {
            InitializeComponent();
        }

        /********/
        // 获取鼠标双击时间
        [DllImport("user32.dll", EntryPoint = "GetDoubleClickTime")]
        public extern static int GetDoubleClickTime();

        private void btnGetDbClickTime_Click(object sender, EventArgs e)
        {
            int nTime = GetDoubleClickTime();
            MessageBox.Show($"{nTime}");
 
        }

        private void btn012_Click(object sender, EventArgs e)
        {
            Cursor.Position = new Point(Cursor.Position.X, Cursor.Position.Y);
            Cursor.Clip = this.groupBox1.Bounds;
        }


        /*
         * 主要用到钩子的安装及释放技术，系统热键的解除屏蔽技术
         */

        // 钩子的安装
 

        private void btn013_Click(object sender, EventArgs e)
        {
            _013Form form = new _013Form();
            form.ShowDialog();
            form.Dispose();
        }
    }
}
