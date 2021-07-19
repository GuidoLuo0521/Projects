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
    /// 获取汉字编码
    /// </summary>
    public partial class eg019_ChineseEncode : Form
    {

        /*
         * X<<N X>>N
         * int uint long ulong byte sbyte short ushort 
         * byte sbyte short ushort 位移操作后，自动转成int
         */

        public eg019_ChineseEncode()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                char ch = this.tbInput.Text[0];

                // 获取 gb2312 编码方式的字节序列
                byte[] bt_gb231 = Encoding.GetEncoding("gb2312").GetBytes(new char[] { ch });
                // 将字节第一个字节左移8位
                int nRet = (int)bt_gb231[0] << 8;
                nRet += (int)bt_gb231[1];

                this.tbOutput.Text = nRet.ToString();
            }
            catch(Exception)
            {
                MessageBox.Show("输入一个汉字");
            }

        }
    }
}
