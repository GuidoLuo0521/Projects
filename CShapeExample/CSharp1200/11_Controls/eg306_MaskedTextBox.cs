using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._11_Controls
{
    public partial class eg306_MaskedTextBox : Form
    {
        public eg306_MaskedTextBox()
        {
            InitializeComponent();

            // 
            this.backgroundWorker1.DoWork += BackgroundWorker1_DoWork;

            // 进度变化的时候
            this.backgroundWorker1.ProgressChanged += BackgroundWorker1_ProgressChanged;

            // 完成的时候
            this.backgroundWorker1.RunWorkerCompleted += BackgroundWorker1_RunWorkerCompleted;

            // 是否报告处理进度
            this.backgroundWorker1.WorkerReportsProgress = true;

            // 是否允许取消
            this.backgroundWorker1.WorkerSupportsCancellation = true;

            this.progressBar1.Minimum = 0;
            this.progressBar1.Maximum = 1000;


        }

        private void BackgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            // 后台执行完毕，弹窗提示
            this.label3.Text = "进度：100%";
            MessageBox.Show("completed!");
        }

        private void BackgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            // 通过进度条显示进度
            // 注意要UI界面添加一个进度条控件和一个label控件

            this.progressBar1.Value = e.ProgressPercentage;
            this.label3.Text = $"进度:{(float)(this.progressBar1.Value) / (float)(this.progressBar1.Maximum) * 100}%";
            this.label3.Update();
        }

        private void BackgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            //当ComputeFibonacci(worker, e)返回时，异步过程结束
            e.Result = ComputeFibonacci(this.backgroundWorker1, e);
        }

        private int ComputeFibonacci(object sender, DoWorkEventArgs e)
        {
            for (int i = 0; i < 1000; i++)
            {
                if (this.backgroundWorker1.CancellationPending)
                {
                    e.Cancel = true;
                    return -1;
                }
                else
                {
                    this.backgroundWorker1.ReportProgress(i);
                }
                System.Threading.Thread.Sleep(10);
            }
            return -1;
        }


        private void maskedTextBox1_MaskInputRejected(object sender, MaskInputRejectedEventArgs e)
        {
            MessageBox.Show($"身份证号不符合规范：{this.maskedTextBox1.Mask.ToString()}");
        }

        private void maskedTextBox2_MaskInputRejected(object sender, MaskInputRejectedEventArgs e)
        {
            MessageBox.Show($"出生日期不符合规范：{this.maskedTextBox2.Mask.ToString()}");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (this.backgroundWorker1.IsBusy)
                return;

            this.backgroundWorker1.RunWorkerAsync();
            this.button1.Enabled = false;
            this.button2.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.button1.Enabled = true;
            this.button2.Enabled = false;
            this.backgroundWorker1.CancelAsync();
            this.backgroundWorker1.Dispose();
        }


        /* 鼠标拖动控件 */
        private void eg306_MaskedTextBox_DragDrop(object sender, DragEventArgs e)
        {
            object data = e.Data.GetData(typeof(Button));
            if(data == button1)
            {
                button1.Top = this.PointToClient(new Point(e.X, e.Y)).Y - ((Point)button1.Tag).Y;
                button1.Left = this.PointToClient(new Point(e.X, e.Y)).X - ((Point)button1.Tag).X;
            }
        }

        private void eg306_MaskedTextBox_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.Move;
        }

        private void eg306_MaskedTextBox_MouseDown(object sender, MouseEventArgs e)
        {
            button1.Tag = e.Location;
            DoDragDrop(button1, DragDropEffects.Move);
        }
    }
}
