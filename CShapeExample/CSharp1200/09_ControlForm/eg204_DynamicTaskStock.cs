
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._09_ControlForm
{

    public partial class eg204_DynamicTaskStock : Form
    {
        private string _Message = "";            // 消息
        private Thread _Td;                 //创建一个线程
        private TcpListener _TcpListener;   //实例化侦听对象

        public eg204_DynamicTaskStock()
        {
            InitializeComponent();
        }


        bool _bCurrentIsBack = true;
        private void Timer1_Tick(object sender, EventArgs e)
        {
            if(_Message.Length > 0)
            {
                if (_bCurrentIsBack)
                {
                    this.notifyIcon1.Icon = Resources.front;
                    _bCurrentIsBack = false;
                }
                else
                {
                    this.notifyIcon1.Icon = Resources.back;
                    _bCurrentIsBack = true;
                }

            }

        }

        private void StartListen()
        {
            IPAddress[] ip = Dns.GetHostAddresses(Dns.GetHostName());
            _TcpListener = new TcpListener(ip[1], 8888);
            _TcpListener.Start();
            while(true)
            {
                TcpClient tcpClient = _TcpListener.AcceptTcpClient();
                NetworkStream stream = tcpClient.GetStream();

                byte[] mbyte = new byte[1024];
                int i = stream.Read(mbyte, 0, mbyte.Length);
                _Message = Encoding.Default.GetString(mbyte, 0, i);

                // 在非创建线程中修改，会出现错误
                //this.richTextBox1.Text = _Message;

                Action action = () =>
                {
                    this.richTextBox1.Text = _Message;
                };
                Invoke(action);
            }
        }


        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                IPAddress[] ip = Dns.GetHostAddresses(Dns.GetHostName());
                string message = this.textBox2.Text;
                TcpClient client = new TcpClient();
                client.Connect(ip[1], 8888);

                NetworkStream networkStream = client.GetStream();
                StreamWriter writer = new StreamWriter(networkStream, Encoding.Default);
                writer.Write(message);
                writer.Flush();
                writer.Close();
                client.Close();
            }
            catch(Exception ex)
            {

            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.timer1.Enabled = false;
        }

        private void eg204_DynamicTaskStock_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (this._TcpListener != null)
            {
                this._TcpListener.Stop();//停止侦听对象
            }
            if (_Td != null)
            {
                if (_Td.ThreadState == ThreadState.Running)//判断线程是否运行
                {
                    _Td.Abort();
                    _Td.Join();
                }
            }

            this.notifyIcon1.Dispose();
            
        }

        private void eg204_DynamicTaskStock_Load(object sender, EventArgs e)
        {
            IPAddress[] ip = Dns.GetHostAddresses(Dns.GetHostName());
            this.textBox1.Text = ip[1].ToString();

            this.timer1.Interval = 500;
            this.timer1.Tick += Timer1_Tick;
            this.timer1.Enabled = true;

            _Td = new Thread(new ThreadStart(this.StartListen));
            _Td.Start();


        }

        private void notifyIcon1_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Normal;
            _Message = "";
        }
    }
}
