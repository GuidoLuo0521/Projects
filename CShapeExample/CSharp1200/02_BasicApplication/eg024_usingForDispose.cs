using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._02_BasicApplication
{
    public partial class eg024_usingForDispose : Form
    {
        public eg024_usingForDispose()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            using (test item = new test()) { item.Show(); }
        }
    }


    class test : IDisposable
    {
        public void Show()
        {
            MessageBox.Show("Show");
        }
        public void Dispose()
        {
            MessageBox.Show("Dispose");
        }
    }

}
