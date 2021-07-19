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
    public partial class eg036_TransChar_ASCII : Form
    {
        public eg036_TransChar_ASCII()
        {
            InitializeComponent();
        }

        /// <summary>
        /// to ascii
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {

                this.textBox3.Text = ((int)this.textBox1.Text[0]).ToString();

                //Encoding encoding = Encoding.GetEncoding("unicode");
                //this.textBox3.Text = encoding.GetBytes(this.textBox1.Text)[0].ToString();
            }
            catch(Exception)
            {
                MessageBox.Show("输入异常");
            }
        }

        /// <summary>
        /// to char
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                int nInput;
                int.TryParse(this.textBox2.Text,out nInput);

                this.textBox4.Text = ((char)(nInput)).ToString();
            }
            catch (Exception)
            {
                MessageBox.Show("输入异常");
            }
        }
    }
}
