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
    public partial class eg039_StringBuilder : Form
    {
        public eg039_StringBuilder()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            StringBuilder stringBuilder = new StringBuilder(richTextBox1.Text);

            for (int i = 0; i < stringBuilder.Length; ++i) 
            {
                if (stringBuilder[i] == ',')
                    stringBuilder.Insert(++i, Environment.NewLine);
            }

            richTextBox2.Text = stringBuilder.ToString();
        }
    }
}
