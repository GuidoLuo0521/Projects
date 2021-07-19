using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200.CSharp1200II.IIChapter2
{
    public partial class Chapter003 : Form
    {
        public Chapter003()
        {
            InitializeComponent();
        }

        delegate void NodeMouseClick(string strNodeName);

        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            switch(e.Node.Name)
            {
                case "034": NodeMouseClick_034(); break;
                case "035": NodeMouseClick_035(); break;
                case "036": NodeMouseClick_036(); break;
                case "037": NodeMouseClick_037(); break;
                case "038": NodeMouseClick_038(); break;
                case "039": NodeMouseClick_039(); break;
                case "040": NodeMouseClick_040(); break;
                case "041": NodeMouseClick_041(); break;
            }

        }

        private void NodeMouseClick_034()
        {
            this.richTextBox1.Text = $"当前时间：{DateTime.Now.ToString()}";
        }
        private void NodeMouseClick_035()
        {
            // 系统目录  system32
            this.richTextBox1.Text = $"系统目录：{Environment.SystemDirectory}";
        }
        private void NodeMouseClick_036()
        {
            // 计算机名称
            this.richTextBox1.Text = $"计算机名称：{Environment.MachineName}";
        }
        private void NodeMouseClick_037()
        {
            // 当前运行目录
            this.richTextBox1.Text = $"运行目录：{Environment.CurrentDirectory}";
        }
        private void NodeMouseClick_038()
        {
            // 系统版本号
            this.richTextBox1.Text = $"系统版本1：{Environment.Version.ToString()}";
            this.richTextBox1.AppendText(Environment.NewLine);
            this.richTextBox1.Text = $"系统版本2：{Environment.OSVersion.ToString()}";
        }
        private void NodeMouseClick_039()
        {
            // 开机运行时间
            this.richTextBox1.Text = $"运行时间：{Environment.TickCount.ToString()}";
        }

        #region 任务栏尺寸
        [DllImport("user32.dll", EntryPoint = "FindWindow")]
        public static extern int FindWindow(string lpClassName, string lpWndName);

        [DllImport("user32.dll", EntryPoint = "GetWindowRect")]
        public static extern int GetWindowRect(int handle, ref Rectangle lpRect);

        #endregion

        private void NodeMouseClick_040()
        {
            // 任务栏尺寸
            this.richTextBox1.Text = $"任务栏尺寸 {Environment.NewLine }";
            Rectangle rect = new Rectangle();
            if (GetWindowRect(FindWindow("Shell_TrayWnd", null), ref rect) == 0)
                return;
            {
                this.richTextBox1.AppendText($"左：{rect.Left}  {Environment.NewLine}");
                this.richTextBox1.AppendText($"上：{rect.Top}  {Environment.NewLine}");
                this.richTextBox1.AppendText($"右：{rect.Right}  {Environment.NewLine}");
                this.richTextBox1.AppendText($"下：{rect.Bottom}  {Environment.NewLine}");

            }


        }
        private void NodeMouseClick_041()
        {
            this.richTextBox1.Text = $"当前时间：{DateTime.Now.ToString()}";
        }

    }
}
