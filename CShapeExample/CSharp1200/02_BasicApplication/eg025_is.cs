using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._02_BasicApplication
{
    public partial class eg025_is : Form
    {
        public eg025_is()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            object obj = this.rb_ObjectFile.Checked ? new FileInfo(@"d:\") : (object)"1111";

            if (this.rb_TypeString.Checked)
                MessageBox.Show(obj is string ? "相同" : "不相同");
            else
                MessageBox.Show(obj is FileInfo ? "相同" : "不相同");
        }
    }
}
