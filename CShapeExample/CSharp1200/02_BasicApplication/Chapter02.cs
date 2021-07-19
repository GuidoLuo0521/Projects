using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._02_BasicApplication
{
    /// <summary>
    /// 第二章窗口
    /// </summary>
    public partial class Chapter02 : Form
    {
        public Chapter02()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 使用异或加密
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button018_Click(object sender, EventArgs e)
        {
            /*
             * 异或运算是，不同为0，相同为1
             */
            eg018_Encrypt form = new eg018_Encrypt();
            form.ShowDialog();
            form.Dispose();
        }

        private void button019_Click(object sender, EventArgs e)
        {
            eg019_ChineseEncode form = new eg019_ChineseEncode();
            form.ShowDialog();
            form.Dispose();
        }

        private void button020_Click(object sender, EventArgs e)
        {
            eg020_LeapYear form = new eg020_LeapYear();
            form.ShowDialog();
            form.Dispose();
        }

        private void button022_Click(object sender, EventArgs e)
        {
            eg022_Overflow form = new eg022_Overflow();
            form.ShowDialog();
            form.Dispose();
        }

        private void button023_Click(object sender, EventArgs e)
        {
            eg023_Typeof form = new eg023_Typeof();
            form.ShowDialog();
            form.Dispose();
        }

        private void button024_Click(object sender, EventArgs e)
        {
            eg024_usingForDispose form = new eg024_usingForDispose();
            form.ShowDialog();
            form.Dispose();
        }

        private void button025_Click(object sender, EventArgs e)
        {
            eg025_is form = new eg025_is();
            form.ShowDialog();
            form.Dispose();
        }

        private void button026_Click(object sender, EventArgs e)
        {

        }

        private void button027_Click(object sender, EventArgs e)
        {
            eg027_GuessNum form = new eg027_GuessNum();
            form.ShowDialog();
            form.Dispose();
        }
    }
}
