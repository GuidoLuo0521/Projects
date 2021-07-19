using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Management;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200.CSharp1200II.IIChapter4
{
    public partial class II074_CRRemoteComputer : Form
    {
        public II074_CRRemoteComputer()
        {
            InitializeComponent();
        }

        private void OperateComputer(string strInfo)
        {
            ConnectionOptions options = new ConnectionOptions();
            options.Username = this.textBoxName.Text;
            options.Password = this.textBoxPassword.Text;

            ManagementScope scope = new ManagementScope("\\\\" + this.maskedTextBox1.Text + "\\root\\cimv2:WIN32_Service", options);
            try 
            {
                scope.Connect();
                ObjectQuery query = new ObjectQuery("SELECT * FROM Win32_OperatingSystem");
                ManagementObjectSearcher searcher = new ManagementObjectSearcher(scope, query);
                ManagementObjectCollection collections = searcher.Get();
                foreach(ManagementObject item in collections)
                {
                    string[] str = { "" };
                    item.InvokeMethod(strInfo, str);
                }
            }
            catch(Exception ex)
            {
                throw ex;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OperateComputer("Shutdown");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            OperateComputer("Reboot");
        }
    }
}
