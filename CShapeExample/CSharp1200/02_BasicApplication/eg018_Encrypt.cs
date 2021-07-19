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
    public partial class eg018_Encrypt : Form
    {
        public eg018_Encrypt()
        {
            InitializeComponent();
        }

        void Show(ref Label label)
        {
            int nEcyptNum = int.Parse(this.tb_EncryptNum.Text);
            int nInputNum = int.Parse(this.tb_Input.Text);

            int nResult = nEcyptNum ^ nInputNum;
            label.Text = nResult.ToString();
        }

        /// <summary>
        /// 加密
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            Show(ref this.label_Encode_Result);
        }
        
        /// <summary>
        /// 解密
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            Show(ref this.label_Dncode_Result);
        }
    }
}
