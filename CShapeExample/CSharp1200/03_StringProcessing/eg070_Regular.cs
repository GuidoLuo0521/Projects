using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._03_StringProcessing
{
    public partial class eg070_Regular : Form
    {
        public eg070_Regular()
        {
            InitializeComponent();
        }

        private void btnPhone_Click(object sender, EventArgs e)
        {
            string strPhone = this.textBox1.Text;
            bool bMatch = System.Text.RegularExpressions.Regex.IsMatch(strPhone, @"^(\d{3,4}-)?\d{6,8}$");
            MessageBox.Show(bMatch ? "是" : "否");
        }

        private void btnPassword_Click(object sender, EventArgs e)
        {
            string strPassword = this.textBox2.Text;
            bool bMatch = System.Text.RegularExpressions.Regex.IsMatch(strPassword, @"^[A-Za-z]+[0-9]$");
            MessageBox.Show(bMatch ? "是" : "否");
        }
    }
}
