using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._05_GenericsClass
{
    public partial class Chapter05 : Form
    {
        public Chapter05()
        {
            InitializeComponent();
        }

        private void button126_Click(object sender, EventArgs e)
        {
            eg126_GenericsClass form = new eg126_GenericsClass();
            form.ShowDialog();
            form.Dispose();
        }
    }
}
