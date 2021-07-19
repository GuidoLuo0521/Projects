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
    public partial class Chapter07 : Form
    {
        public Chapter07()
        {
            InitializeComponent();

            this.StartPosition = new FormStartPosition();
            
        }

        private void button157_Click(object sender, EventArgs e)
        {
            eg157_FormStartPosition form = new eg157_FormStartPosition();
            form.ShowDialog();
            form.Dispose();

        }

        private void button159_Click(object sender, EventArgs e)
        {
            eg159_StartWithLastLocaltion form = new eg159_StartWithLastLocaltion();
            form.ShowDialog();
            form.Dispose();
        }

        private void button168_Click(object sender, EventArgs e)
        {
            eg168_FlashWindow form = new eg168_FlashWindow();
            form.ShowDialog();
            form.Dispose();
        }

        private void button174_Click(object sender, EventArgs e)
        {
            eg174_ClearForm form = new eg174_ClearForm();
            form.ShowDialog();
            form.Dispose();
        }
    }
}

