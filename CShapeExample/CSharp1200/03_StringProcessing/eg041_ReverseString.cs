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
    public partial class eg041_ReverseString : Form
    {
        public eg041_ReverseString()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            char[] array = this.textBox1.Text.ToCharArray();
            Array.Reverse(array);
            this.textBox2.Text = new StringBuilder().Append(array).ToString() ;
        }
    }
}
