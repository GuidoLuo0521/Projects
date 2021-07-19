using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._07_WindowsBase
{
    public partial class eg157_FormStartPosition : Form
    {
        public eg157_FormStartPosition()
        {
            InitializeComponent();

            this.StartPosition = FormStartPosition.CenterParent;
//             this.StartPosition = FormStartPosition.CenterScreen;
//             this.StartPosition = FormStartPosition.Manual;
//             this.StartPosition = FormStartPosition.WindowsDefaultBounds;
//             this.StartPosition = FormStartPosition.WindowsDefaultLocation;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Left = int.Parse(this.textBox1.Text);
            this.Top = int.Parse(this.textBox2.Text);
        }
    }
}
