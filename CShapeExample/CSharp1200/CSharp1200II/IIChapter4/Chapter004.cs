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

namespace CSharp1200.CSharp1200II.IIChapter4
{
    public partial class Chapter004 : Form
    {
        public Chapter004()
        {
            InitializeComponent();

            this.treeView1.ExpandAll();
            
        }

        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            switch (e.Node.Name)
            {
                case "069": NodeMouseClick_069(); break;
                case "070": NodeMouseClick_070(); break;
                case "071": NodeMouseClick_071(); break;
                case "072": NodeMouseClick_072(); break;
                case "073": NodeMouseClick_073(); break;
                case "074": NodeMouseClick_074(); break;
            }
        }

        private void NodeMouseClick_074()
        {
            // 远程关闭计算机
            /*
             * 主要用到WMI管理对象中的类 
             * ConnectionOptions：指定生成WMI连接所需的所有设置，Username, Password
             * ManagementScope：表示管理操作的范围
             * ObjectQuery：表示返回实例或类的管理查询
             * ManagementObjectSearcher：基于指定的查询检索管理对象的集合，比如枚举系统磁盘，网络适配器，进程及更对管理对象
             *  或者用于查询所有处于活动状态的网络连接以及暂停的服务等。
             * 
             */

            II074_CRRemoteComputer form = new II074_CRRemoteComputer();
            form.ShowDialog();
            form.Dispose();

        }

        private void NodeMouseClick_073()
        {
            //   定时关闭计算机 

        }

        private void NodeMouseClick_072()
        {
            
            // 实现注销、关闭和重启计算机
        }

        private void NodeMouseClick_071()
        {
            // 禁止用户关闭计算机
        }

        private void NodeMouseClick_070()
        {
            // 切换到睡眠状态
            if (MessageBox.Show(this, "现在休眠？", "提示内容") == DialogResult.OK)
            {
                Application.SetSuspendState(PowerState.Suspend, true, false);
            }
        }

        private void NodeMouseClick_069()
        {
            // 进入Windows前发出警告
            /*
             * 通过设置注册表中HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\Winlogon子键下的
             * LegalNoticeCaption 和 LegalNoticeText项的值来实现
             * 
             * 注册表主要通过 RegistryKey 类来实现。
             * RegistryKey封装了对类的基本操作
             *      CreateSubKey()  -->  创建新子项或打开一个现有子项以进行写访问。
             *      SetValue()  -->  使用指定的注册表数据类型设置注册表项中的名称/值对的值
             */
            if (this.richTextBox1.Text == "")
            {
                MessageBox.Show(this, "请输入文字", "提示内容");
                return;
            }
                
            
            if(MessageBox.Show(this, this.richTextBox1.Text,"重启提示内容") == DialogResult.OK)
            {
                RegistryKey key = Registry.LocalMachine;   // 获取配置表中 LocalMachine 中的值
                RegistryKey registry = key.CreateSubKey(@"SOFTWARE\Microsoft\WindowsNT\CurrentVersion\Winlogon");// 创建注册表
                registry.SetValue("LegalNoticeCaption", this.richTextBox1.Text, RegistryValueKind.String);

                if (MessageBox.Show(this, "重启生效，现在重启？") == DialogResult.OK)
                {

                }
            }
        }
    }
}
