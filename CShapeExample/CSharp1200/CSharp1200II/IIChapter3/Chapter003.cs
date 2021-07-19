using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Printing;
using System.IO;
using System.Linq;
using System.Management;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200.CSharp1200II.IIChapter3
{
    public partial class Chapter003 : Form
    {
        public Chapter003()
        {
            InitializeComponent();

            this.toolTip1.InitialDelay = 500;
            this.toolTip1.ReshowDelay = 500;
            this.toolTip1.ShowAlways = true;
            this.toolTip1.SetToolTip(this.treeView1, "目录");

            this.treeView1.Nodes[0].Expand();
            this.treeView1.Nodes[0].Nodes[this.treeView1.Nodes[0].GetNodeCount(false)-1].Expand();
        }

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
                case "042": NodeMouseClick_042(); break;
                case "043": NodeMouseClick_043(); break;
                case "044": NodeMouseClick_044(); break;
                case "045": NodeMouseClick_045(); break;
                case "046": NodeMouseClick_046(); break;
                case "047": NodeMouseClick_047(); break;
                case "048": NodeMouseClick_048(); break;
                case "049": NodeMouseClick_049(); break;
                case "050": NodeMouseClick_050(); break;
                case "051": NodeMouseClick_051(); break;
                case "052": NodeMouseClick_052(); break;
                case "053": NodeMouseClick_053(); break;
                case "054": NodeMouseClick_054(); break;
                case "055": NodeMouseClick_055(); break;
                case "056": NodeMouseClick_056(); break;
                case "057": NodeMouseClick_057(); break;
                case "058": NodeMouseClick_058(); break;
                case "059": NodeMouseClick_059(); break;
                case "060": NodeMouseClick_060(); break;
                case "061": NodeMouseClick_061(); break;
                case "062": NodeMouseClick_062(); break;
                case "063": NodeMouseClick_063(); break;
                case "064": NodeMouseClick_064(); break;
                case "065": NodeMouseClick_065(); break;
                case "066": NodeMouseClick_066(); break;
                case "067": NodeMouseClick_067(); break;
                case "068": NodeMouseClick_068(); break;
            }
        }

        private void NodeMouseClick_068()
        {
            EventLog log = new EventLog();
            log.Source = "Application";
            log.WriteEntry("NodeMouseClick_066");
        }

        private void NodeMouseClick_067()
        {
            EventLog log = new EventLog();
            log.Source = "System";
            log.WriteEntry("NodeMouseClick_066");
        }

        private void NodeMouseClick_066()
        {
            // 创建并写入自定义日志信息
            /*
             * 主要用到了EventLog类的 SourceExists方法，CreateEventSource方法，Source WriteEntry属性
             *      SourceExists()  -->     用来在计算机的注册表中搜索给定的时间源。
             *      CreateEventSource() -->     用来建立一个能够将事件信息写入到系统的特定日志的应用程序。
             *      Source 获取和何止在写入事件日志时要注册和使用的源名称。
             *      WriteEntry 主要用来将 项写入事件日志
             */

            string strAppEventLogSrc = "CSharp1200";
            if (!EventLog.SourceExists(strAppEventLogSrc))
            {
                EventLog.CreateEventSource(strAppEventLogSrc, "Application");
            }

            EventLog log = new EventLog();
            log.Source = strAppEventLogSrc;
            log.WriteEntry("NodeMouseClick_066");

        }

        private void NodeMouseClick_065()
        {
            // 显示程序日志
            this.richTextBox1.Text = "";

            this.eventLog1.Log = "Application";      // 指定安全日志
            EventLogEntryCollection collection = eventLog1.Entries;
            int nCount = collection.Count;
            string strInfo = $"显示程序日志：{nCount}个事件";
            this.richTextBox1.AppendText(strInfo + Environment.NewLine);
            int i = 0;
            foreach (EventLogEntry entry in collection)
            {
                this.richTextBox1.AppendText($"类型：{entry.EntryType}{Environment.NewLine}");
                this.richTextBox1.AppendText($"日期：{entry.TimeGenerated.ToLongDateString()}{Environment.NewLine}");
                this.richTextBox1.AppendText($"时间：{entry.TimeGenerated.ToLongTimeString()}{Environment.NewLine}");
                this.richTextBox1.AppendText($"来源：{entry.Source}{Environment.NewLine}");
                this.richTextBox1.AppendText($"事件：{entry.InstanceId.ToString()}{Environment.NewLine}");
                this.richTextBox1.AppendText($"用户：{entry.UserName}{Environment.NewLine}");
                this.richTextBox1.AppendText($"计算机：{entry.MachineName}{Environment.NewLine}");
                this.richTextBox1.AppendText(Environment.NewLine);

                if (i++ > 20)
                    break;
            }
        }

        private void NodeMouseClick_064()
        {
            this.richTextBox1.Text = "";

            this.eventLog1.Log = "Security";      // 指定安全日志
            EventLogEntryCollection collection = eventLog1.Entries;
            int nCount = collection.Count;
            string strInfo = $"显示安全日志：{nCount}个事件";
            this.richTextBox1.AppendText(strInfo + Environment.NewLine);
            int i = 0;
            foreach (EventLogEntry entry in collection)
            {
                this.richTextBox1.AppendText($"类型：{entry.EntryType}{Environment.NewLine}");
                this.richTextBox1.AppendText($"日期：{entry.TimeGenerated.ToLongDateString()}{Environment.NewLine}");
                this.richTextBox1.AppendText($"时间：{entry.TimeGenerated.ToLongTimeString()}{Environment.NewLine}");
                this.richTextBox1.AppendText($"来源：{entry.Source}{Environment.NewLine}");
                this.richTextBox1.AppendText($"事件：{entry.InstanceId.ToString()}{Environment.NewLine}");
                this.richTextBox1.AppendText($"用户：{entry.UserName}{Environment.NewLine}");
                this.richTextBox1.AppendText($"计算机：{entry.MachineName}{Environment.NewLine}");
                this.richTextBox1.AppendText(Environment.NewLine);

                if (i++ > 20)
                    break;
            }
        }

        private void NodeMouseClick_063()
        {
            // 获取系统日志
            /*
             * 主要包含Windows系统组件记录的事件，比如在启动过程中加载驱动程序或其他系统组件失败等信息。
             * EventLog 类 Log属性，Entries属性
             *      主要用来提供与Windows事件日志的交互。 
             *      1）Log属性用来获取或设置读取或谢日的日志名称。
             *      2）Entries属性，获取时间日志的内容
             * EventLogEntry 类
             *      在日志中封装单个记录
             * EventLogEntryCollection类 Count属性            
             *      定义EventLogEntry实例集合的大小和枚举数
             *      1) Count 获取时间日志的项数。
             */

            this.richTextBox1.Text = "";

            this.eventLog1.Log = "System";      // 指定系统日志
            EventLogEntryCollection collection = eventLog1.Entries;
            int nCount = collection.Count;
            string strInfo = $"显示系统日志：{nCount}个事件";
            this.richTextBox1.AppendText(strInfo + Environment.NewLine);
            int i = 0;
            foreach(EventLogEntry entry in collection)
            {
                this.richTextBox1.AppendText($"类型：{entry.EntryType}{Environment.NewLine}");
                this.richTextBox1.AppendText($"日期：{entry.TimeGenerated.ToLongDateString()}{Environment.NewLine}");
                this.richTextBox1.AppendText($"时间：{entry.TimeGenerated.ToLongTimeString()}{Environment.NewLine}");
                this.richTextBox1.AppendText($"来源：{entry.Source}{Environment.NewLine}");
                this.richTextBox1.AppendText($"事件：{entry.InstanceId.ToString()}{Environment.NewLine}");
                this.richTextBox1.AppendText($"用户：{entry.UserName}{Environment.NewLine}");
                this.richTextBox1.AppendText($"计算机：{entry.MachineName}{Environment.NewLine}");
                this.richTextBox1.AppendText(Environment.NewLine);

                if (i++ > 20)
                    break;
            }
        }

        private void NodeMouseClick_062()
        {
            // 用户权限
            /*
             * WindowsPrincipal类 允许检查windows用户的组成成员身份
             * 
             * IsInRole() 方法 判定是否属于指定用户组。
             * 
             * Windows域是计算机网络的一种形式，其中所有用户帐户 ，计算机，打印机和其他安全主体都在位于称为域控制器的一个或多个中央计算机集群上的中央数据库中注册。
             * 身份验证在域控制器上进行。
             * 在域中使用计算机的每个人都会收到一个唯一的用户帐户，然后可以为该帐户分配对该域内资源的访问权限。
             * 从Windows Server 2003开始 ， Active Directory是负责维护该中央数据库的Windows组件。
             * Windows域的概念与工作组的概念形成对比，在该工作组中，每台计算机都维护自己的安全主体数据库。
             */
            this.richTextBox1.Text = "";

            // 获取当前域
            AppDomain domain = System.Threading.Thread.GetDomain();
            // 将操作系统组映射到角色
            domain.SetPrincipalPolicy(System.Security.Principal.PrincipalPolicy.WindowsPrincipal);
            // 获取当前系统组
            System.Security.Principal.WindowsPrincipal principal = (System.Security.Principal.WindowsPrincipal)System.Threading.Thread.CurrentPrincipal;

            if(principal.IsInRole(System.Security.Principal.WindowsBuiltInRole.User))
            {
                this.richTextBox1.AppendText("普通用户");
            }
            if (principal.IsInRole(System.Security.Principal.WindowsBuiltInRole.PowerUser))
            {
                this.richTextBox1.AppendText("超级用户");
            }
        }

        private void NodeMouseClick_061()
        {
            // 获取当前用户
            this.richTextBox1.Text = "";

            this.richTextBox1.AppendText("Dns.GetHostName():" + Dns.GetHostName() + Environment.NewLine );
            this.richTextBox1.AppendText("Environment.UserName:" + Environment.UserName);


        }

        private void NodeMouseClick_060()
        {
            // 获取映射驱动器路径
            this.richTextBox1.Text = "";

            try
            {
                SelectQuery query = new SelectQuery("SELECT * FROM win32_logicaldisk");
                ManagementObjectSearcher driveID = new ManagementObjectSearcher(query);
                foreach (ManagementObject disk in driveID.Get())
                {
                    string strType = disk["DriveType"].ToString();
                    if (strType == "4")
                        this.richTextBox1.Text = disk["Name"].ToString();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("参数错误");
            }
        }

        private void NodeMouseClick_059()
        {
            // 运行Exe路径
            this.richTextBox1.AppendText("ExecutablePath:" + Application.ExecutablePath + Environment.NewLine) ;
            this.richTextBox1.AppendText("StartupPath:" + Application.StartupPath + Environment.NewLine);
        }

        private void NodeMouseClick_058()
        {
            // 系统特殊文件夹
            /*
             *  Enum 类 
             */
            this.richTextBox1.Text = "";
            
            Array array = Enum.GetValues(typeof(Environment.SpecialFolder));

            foreach(object item in array)
            {
                this.richTextBox1.AppendText(item.ToString() + ":" + Environment.NewLine + "    ");
                this.richTextBox1.AppendText(Environment.GetFolderPath((Environment.SpecialFolder)item));
                this.richTextBox1.AppendText(Environment.NewLine);
            }
        }

        private void NodeMouseClick_057()
        {
            // 是否脱机状态
            /*
             * 判断当前系统电源  关闭：脱机 否则：联机
             * 既然脱机 就是 没联网，那用联网就可以了撒
             *      
             */

            this.richTextBox1.Text = "";

            switch(SystemInformation.PowerStatus.PowerLineStatus)
            {
                case PowerLineStatus.Offline: this.richTextBox1.Text = "脱机"; break;
                case PowerLineStatus.Online: this.richTextBox1.Text = "联机"; break;
                case PowerLineStatus.Unknown: this.richTextBox1.Text = "未知"; break;
            }
        }

        private void NodeMouseClick_056()
        {
            // 检测是否联网
            this.richTextBox1.Text = "";
            this.richTextBox1.Text = SystemInformation.Network ? "已联网" : "未联网";
        }

        private void NodeMouseClick_055()
        {
            // 获取本机IP地址
            /*
             * Dns类 GetHostByName() : 获取DNS主机名的DNS信息 返回IPHostEntry对象
             * Dns类 GetHostName() : 获取DNS主机名
             *  
             */
            this.richTextBox1.Text = "";

            string strHostName = Dns.GetHostName();
            this.richTextBox1.AppendText("本机名称：" + strHostName + Environment.NewLine);

            IPHostEntry iPHostEntry =  Dns.GetHostEntry(strHostName);
            foreach(IPAddress iP in iPHostEntry.AddressList)
            {
                this.richTextBox1.AppendText("  " + iP.ToString() + Environment.NewLine);
            }

        }

        private void NodeMouseClick_054()
        {
            // 获取安装打印机信息
            /*
             * PrinterSettings (类):用来指定打印文档信息
             * 
             *      InstalledPrinters（属性）：获取安装打印机名
             */
            this.richTextBox1.Text = "";

            foreach(string str in PrinterSettings.InstalledPrinters)
            {
                this.richTextBox1.SelectionStart = this.richTextBox1.Text.Length;
                this.richTextBox1.SelectionLength = 0;
                this.richTextBox1.SelectionFont = new System.Drawing.Font("宋体", 15F);
                this.richTextBox1.SelectionColor = Color.Red;
                this.richTextBox1.AppendText("打印机名称：" + str + Environment.NewLine);
                this.richTextBox1.SelectionColor = this.richTextBox1.ForeColor;
                this.richTextBox1.SelectionFont = this.richTextBox1.Font;

                PrinterSettings printer = new PrinterSettings();
                if(printer.IsValid)
                {
 
                    foreach (PrinterResolution resolution in printer.PrinterResolutions)
                    {
                        this.richTextBox1.AppendText("  分辨率：" + resolution.ToString() + Environment.NewLine);
                    }

                    foreach (PaperSize paperSize in printer.PaperSizes)
                    {
                        this.richTextBox1.AppendText("  尺寸：" + paperSize.ToString() + Environment.NewLine);
                    }
                }
            }


        }

        private void NodeMouseClick_053()
        {
            // 屏幕分辨率
            this.richTextBox1.Text = "";
            this.richTextBox1.AppendText("宽：" + SystemInformation.VirtualScreen.Width.ToString());
            this.richTextBox1.AppendText(Environment.NewLine);
            this.richTextBox1.AppendText("高：" + SystemInformation.VirtualScreen.Height.ToString());
            
        }

        private void NodeMouseClick_052()
        {
            // 获取声音设备的名称及PNPDeviceID
            this.richTextBox1.Text = "";

            try
            {                
                SelectQuery query = new SelectQuery("SELECT * FROM Win32_SoundDevice");
                ManagementObjectSearcher driveID = new ManagementObjectSearcher(query);
                foreach (ManagementObject mo in driveID.Get())
                {
                    this.richTextBox1.AppendText("名称：" + mo["name"].ToString() + Environment.NewLine);
                    this.richTextBox1.AppendText("PNPDeviceID：" + mo["PNPDeviceID"].ToString() + Environment.NewLine);
                    this.richTextBox1.AppendText(Environment.NewLine);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("参数错误");
            }
        }

        private void NodeMouseClick_051()
        {
            // 获取显示设备的名称及PNPDeviceID
            this.richTextBox1.Text = "";

            try
            {
                // SelectQuery query = new SelectQuery("SELECT * FROM Win32_VideoContrroller");
                SelectQuery query = new SelectQuery("SELECT * FROM Win32_VideoController");
                ManagementObjectSearcher driveID = new ManagementObjectSearcher(query);
                foreach (ManagementObject mo in driveID.Get())
                {
                    this.richTextBox1.AppendText("名称：" + mo["name"].ToString() + Environment.NewLine);
                    this.richTextBox1.AppendText("PNPDeviceID：" + mo["PNPDeviceID"].ToString() + Environment.NewLine);
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show("参数错误");
            }

        }

        private void NodeMouseClick_050()
        {
            // 磁盘信息
            this.richTextBox1.Text = "";

            DriveInfo[] items = DriveInfo.GetDrives();
            try
            {
                foreach (DriveInfo item in items)
                {
                    this.richTextBox1.AppendText("磁盘名称：" + item.Name + Environment.NewLine);
                    this.richTextBox1.AppendText("  驱动器类型：" + item.DriveType + Environment.NewLine);
                    if (item.IsReady)    // try
                    {
                        this.richTextBox1.AppendText("  卷标：" + item.VolumeLabel + Environment.NewLine);
                        this.richTextBox1.AppendText("  磁盘格式：" + item.DriveFormat + Environment.NewLine);
                        this.richTextBox1.AppendText("  可用空间：" + (item.TotalSize / 1024 / 1024 / 1024).ToString() + "G" + Environment.NewLine);
                        this.richTextBox1.AppendText("  剩余空间：" + (item.TotalFreeSpace / 1024 / 1024 / 1024).ToString() + "G" + Environment.NewLine);
                    }

                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void NodeMouseClick_049()
        {
            // 获取磁盘类型 NTFS 和 FAT32
            // NTFS 格式相对于 FAT32 来讲，包含Active Directory所需的功能以及其他的重要安全性功能。
            this.richTextBox1.Text = "";

            DriveInfo[] items = DriveInfo.GetDrives();
            try
            {
                foreach (DriveInfo item in items)
                {
                    if (item.IsReady)    // try
                    {
                        this.richTextBox1.AppendText("磁盘名称：" + item.Name + Environment.NewLine);
                        this.richTextBox1.AppendText("  磁盘类型：" + item.DriveFormat + Environment.NewLine);
                    }

                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void NodeMouseClick_048()
        {
            // 获取磁盘空间
            this.richTextBox1.Text = "";

            DriveInfo[] items = DriveInfo.GetDrives();
            try
            {
                foreach (DriveInfo item in items)
                {
                    if(item.IsReady)    // try
                    {
                        this.richTextBox1.AppendText("磁盘名称：" + item.Name + Environment.NewLine);
                        this.richTextBox1.AppendText("  可用空间：" + (item.TotalSize / 1024 / 1024 / 1024).ToString() + "G" + Environment.NewLine);
                        this.richTextBox1.AppendText("  剩余空间：" + (item.TotalFreeSpace / 1024 / 1024 / 1024).ToString() + "G" + Environment.NewLine);
                    }

                }
            }
            catch(Exception ex)
            {
                throw ex;
            }
        }

        private void NodeMouseClick_047()
        {
            //  获取所有逻辑分区
            this.richTextBox1.Text = "";
            string[] strDrives = Directory.GetLogicalDrives();
            foreach (string str in strDrives)
            {
                this.richTextBox1.AppendText(str + Environment.NewLine);
            }
        }

        private void NodeMouseClick_046()
        {
            // 硬盘序列号
            // 一般硬盘序列号 用作软件加密手段
            this.richTextBox1.Text = "";

            SelectQuery query = new SelectQuery("SELECT * FROM Win32_PhysicalMedia");
            ManagementObjectSearcher driveID = new ManagementObjectSearcher(query);

            string strDiskID = "";
            foreach (ManagementObject mo in driveID.Get())
            {
                strDiskID = mo["SerialNumber"].ToString().Trim();
                break;
            }

            this.richTextBox1.Text = $"硬盘序列号：{strDiskID}";
        }

        private void NodeMouseClick_045()
        {
            // 获取主板型号
            // 采用 SelectQuery
            this.richTextBox1.Text = "";

            SelectQuery query = new SelectQuery("SELECT * FROM Win32_BaseBoard");
            ManagementObjectSearcher driveID = new ManagementObjectSearcher(query);

            ManagementObjectCollection.ManagementObjectEnumerator data = driveID.Get().GetEnumerator();
            data.MoveNext();    //循环读取

            ManagementBaseObject baseObject = data.Current;
            try
            {
                //this.richTextBox1.AppendText(baseObject.GetPropertyValue("SeriaNumber").ToString());  ==> 使用 try

                this.richTextBox1.AppendText(baseObject.GetPropertyValue("SerialNumber").ToString() + Environment.NewLine);
                this.richTextBox1.AppendText(baseObject.GetPropertyValue("Manufacturer").ToString() + Environment.NewLine);
                this.richTextBox1.AppendText(baseObject.GetPropertyValue("Product").ToString() + Environment.NewLine);
            }
            catch (Exception ex)
            {
                this.richTextBox1.AppendText("input key is error");
            }
                

        }

        private void NodeMouseClick_044()
        {
            // 获取CPU 型号
            this.richTextBox1.Text = "";
            ManagementClass management = new ManagementClass("Win32_processor");
            ManagementObjectCollection moc = management.GetInstances();
            foreach(ManagementObject mo in moc)
            {
                this.richTextBox1.AppendText(mo["processorid"].ToString());
                this.richTextBox1.AppendText(Environment.NewLine);
            }

            ManagementObjectSearcher driveID = new ManagementObjectSearcher("SELECT * FROM Win32_processor");
            foreach(ManagementObject mo in  driveID.Get())
            {
                this.richTextBox1.AppendText(mo["Manufacturer"].ToString() + Environment.NewLine);
                this.richTextBox1.AppendText(mo["Version"].ToString() + Environment.NewLine);
                this.richTextBox1.AppendText(mo["Name"].ToString() + Environment.NewLine);
            }
            
        }



        private void NodeMouseClick_043()
        {
            /*
             * WMI 管理类
             * ManagementObjectSearcher : 基于指定的查询检索管理对象的集合
             * 比如：枚举系统所有磁盘驱动器，网络适配器，进程和更多的管理对象，
             * 或者用于查询所有处于活动状态的网络连接以及暂停的服务。
             */
            this.richTextBox1.Text = "";
            string strKey = "Win32_PhysicalMemory";

            ManagementObjectSearcher searchers = new ManagementObjectSearcher("select * from " + strKey);
            try
            {
                foreach(ManagementObject share in searchers.Get())
                {
                    this.richTextBox1.AppendText("CPU编号：" + share["name"].ToString() + Environment.NewLine);

                    foreach(PropertyData pc in share.Properties)
                    {
                        if(pc.Value != null && pc.Value.ToString() != "")
                        {
                            this.richTextBox1.AppendText(pc.Value.ToString() + Environment.NewLine);
                            this.richTextBox1.AppendText(Environment.NewLine);
                        }
                    }
                }
            }
            catch(Exception ex)
            {

            }


        }

        private void NodeMouseClick_042()
        {
            // 系统环境变量
            this.richTextBox1.Text = "";
            IDictionary variables = Environment.GetEnvironmentVariables();
            foreach(DictionaryEntry entry in variables)
            {
                this.richTextBox1.AppendText(entry.Key.ToString() + Environment.NewLine);
                this.richTextBox1.AppendText(entry.Value.ToString() + Environment.NewLine);
                this.richTextBox1.AppendText(Environment.NewLine);
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
            this.richTextBox1.Text = $"运行时间：{(Environment.TickCount / 1000 / 60).ToString()}min";
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
