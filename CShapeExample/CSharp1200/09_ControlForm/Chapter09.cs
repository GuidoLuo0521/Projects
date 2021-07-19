using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._09_ControlForm
{
    public partial class Chapter09 : Form
    {
        public Chapter09()
        {
            InitializeComponent();
        }

        private void button200_Click(object sender, EventArgs e)
        {
            eg200_DragImageToForm form = new eg200_DragImageToForm();
            form.ShowDialog();
            form.Dispose();
        }

        private void button204_Click(object sender, EventArgs e)
        {
            eg204_DynamicTaskStock form = new eg204_DynamicTaskStock();
            form.ShowDialog();
            form.Dispose();       
        }

        private void button205_Click(object sender, EventArgs e)
        {
            eg205_BubbleShowForm form = new eg205_BubbleShowForm();
            form.ShowDialog();
            form.Dispose();
        }
    }
}
