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
    public partial class eg042_RemoveBlank : Form
    {
        public eg042_RemoveBlank()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            char[] array = textBox1.Text.ToCharArray();

//             System.Collections.IEnumerator ts = array.GetEnumerator();
//             ts.MoveNext();


            StringBuilder stringBuilder = new StringBuilder();
            foreach(char item in array)
            {
                if (item != ' ')
                    stringBuilder.Append(item);
            }

            this.textBox2.Text = stringBuilder.ToString();
        }
    }
}
