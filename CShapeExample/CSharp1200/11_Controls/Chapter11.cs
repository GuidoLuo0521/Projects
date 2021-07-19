using CSharp1200._15_FileOpreate;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._11_Controls
{
    public partial class Chapter11 : Form
    {
        public Chapter11()
        {
            InitializeComponent();
        }

        private void button265_Click(object sender, EventArgs e)
        {
            eg265_TreeView form = new eg265_TreeView();
            form.ShowDialog();
            form.Dispose();
        }

        private void button306_Click(object sender, EventArgs e)
        {
            eg306_MaskedTextBox form = new eg306_MaskedTextBox();
            form.ShowDialog();
            form.Dispose();
        }

        private void button384_Click(object sender, EventArgs e)
        {
            eg383_FileSplite form = new eg383_FileSplite();
            form.ShowDialog();
            form.Dispose();
        }
    }
}
