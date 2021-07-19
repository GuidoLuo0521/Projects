using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._08_SpecialForm
{
    public partial class Chapter08 : Form
    {
        public Chapter08()
        {
            InitializeComponent();
        }

        private void button176_Click(object sender, EventArgs e)
        {
            eg176_OutLookForm form = new eg176_OutLookForm();
            form.ShowDialog();
            form.Dispose();
        }

        private void button181_Click(object sender, EventArgs e)
        {
            eg181_SplitContainer form = new eg181_SplitContainer();
            form.ShowDialog();
            form.Dispose();
        }

        private void button182_Click(object sender, EventArgs e)
        {
            eg182_AnimationForm form = new eg182_AnimationForm();
            form.ShowDialog();
            form.Dispose();
        }
    }
}
