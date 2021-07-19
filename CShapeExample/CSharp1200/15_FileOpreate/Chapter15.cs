using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._15_FileOpreate
{
    public partial class Chapter15 : Form
    {
        public Chapter15()
        {
            InitializeComponent();
        }

        private void button400_Click(object sender, EventArgs e)
        {
            eg400_FileOpreater form = new eg400_FileOpreater();
            form.ShowDialog();
            form.Dispose();
        }
    }
}
