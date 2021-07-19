using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._10_MDIForm
{
    public partial class Chapter10 : Form
    {
        public Chapter10()
        {
            InitializeComponent();
        }

        private void button210_Click(object sender, EventArgs e)
        {
            eg210_MDIParent form = new eg210_MDIParent();
            form.ShowDialog();
            form.Dispose();
        }
    }
}
