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
    public partial class Chapter03 : Form
    {
        public Chapter03()
        {
            InitializeComponent();
        }

        private void button036_Click(object sender, EventArgs e)
        {
            eg036_TransChar_ASCII form = new eg036_TransChar_ASCII();
            form.ShowDialog();
            form.Dispose();
        }

        private void button039_Click(object sender, EventArgs e)
        {
            eg039_StringBuilder form = new eg039_StringBuilder();
            form.ShowDialog();
            form.Dispose();
        }

        private void button041_Click(object sender, EventArgs e)
        {
            eg041_ReverseString form = new eg041_ReverseString();
            form.ShowDialog();
            form.Dispose();
        }

        private void button042_Click(object sender, EventArgs e)
        {
            eg042_RemoveBlank form = new eg042_RemoveBlank();
            form.ShowDialog();
            form.Dispose();
        }

        private void button070_Click(object sender, EventArgs e)
        {
            eg070_Regular form = new eg070_Regular();
            form.ShowDialog();
            form.Dispose();
        }
    }
}
