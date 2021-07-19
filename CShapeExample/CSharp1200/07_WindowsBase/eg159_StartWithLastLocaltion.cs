using Microsoft.Win32;
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
    public partial class eg159_StartWithLastLocaltion : Form
    {
        public eg159_StartWithLastLocaltion()
        {
            InitializeComponent();
        }

        private void eg159_StartWithLastLocaltion_Load(object sender, EventArgs e)
        {

            int nDeskW = Screen.PrimaryScreen.WorkingArea.Width;
            int nDeskH = Screen.PrimaryScreen.WorkingArea.Height;
            this.Width = (int)(nDeskW * 0.8);
            this.Height = (int)(nDeskH * 0.7);

            RegistryKey registry, registry1;
            registry = Registry.CurrentUser;

            try
            {
                registry1 = registry.CreateSubKey("Software\\MySoft");
                this.Location = new Point(Convert.ToInt32(registry1.GetValue("x")), Convert.ToInt32(registry1.GetValue("y")));
            }
            catch
            {
                MessageBox.Show("未找到位置");
            }
        }

        private void eg159_StartWithLastLocaltion_FormClosed(object sender, FormClosedEventArgs e)
        {

            RegistryKey registry, registry1;
            registry = Registry.CurrentUser;
            registry1 = registry.CreateSubKey("Software\\MySoft");

            try
            {
                registry1.SetValue("x", this.Location.X.ToString());
                registry1.SetValue("y", this.Location.Y.ToString());
            }
            catch
            {

            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (this.TopMost == true)
            {
                this.TopMost = false;
                this.button1.Text = "始终顶层";
            }
            else
            {
                this.TopMost = true;
                this.button1.Text = "取消顶层";
            }
        }
    }
}
