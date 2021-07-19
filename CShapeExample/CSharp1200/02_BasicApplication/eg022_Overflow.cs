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
    /// check 判定是否溢出
    /// </summary>
    public partial class eg022_Overflow : Form
    {
        public eg022_Overflow()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte btParam1, btParam2;
            if (byte.TryParse(textBox1.Text, out btParam1) && byte.TryParse(textBox2.Text, out btParam2))
            {
                try
                {
                    /*
                     * 会对程序造成性能影响，合理使用还是可以的
                     */
                    checked
                    {
                        btParam1 += btParam2;
                        textBox3.Text = btParam1.ToString();
                    }
                }
                catch(OverflowException ex)
                {
                    MessageBox.Show(this, "溢出");
                }
            }
            else
            {
                MessageBox.Show(this, "输入255以内数字");
            }


        }
    }
}
