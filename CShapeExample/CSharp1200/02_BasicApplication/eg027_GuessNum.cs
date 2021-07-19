using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._02_BasicApplication
{
    public partial class eg027_GuessNum : Form
    {
        private int _nRandNum = -1;
        private Thread _Thread = null;
        private bool _bGuessSuccess = false;

        public eg027_GuessNum()
        {
            InitializeComponent();
        }

        private void CreateButton()
        {
            for (int i = 0; i < 10; ++i)
            {
                for (int j = 0; j < 10; ++j)
                {
                    Button button = new Button();
                    button.Width = 35;
                    button.Height = 35;
                    button.Location = new Point(j * button.Width, i * button.Height + 80);
                    button.Text = (j + i * 10).ToString();
                    button.Click += Button_Click;
                    this.Controls.Add(button);
                }
            }
        }

        private void RemoveButton()
        {
            foreach (Control control in this.Controls)
            {
                if (control is Button)
                {
                    control.Enabled = true;

                    if (control.Name == "button1")
                        continue;

                    Controls.Remove(control);
                }
            }
        }

        private void Button_Click(object sender, EventArgs e)
        {
            if (_Thread == null)
                return;

            if(sender is Button)
            {
                Button button = ((Button)sender);
                int nSel = -1;
                int.TryParse(button.Text, out nSel);
                if (nSel == -1)
                    return;

                if (nSel < _nRandNum)
                {
                    button.BackColor = Color.Red;
                    //这里可能触发异常
                    button.Text = "小";
                    button.Enabled = false;
                }    
                else if (nSel > _nRandNum)
                {
                    button.BackColor = Color.Red;
                    button.Text = "大";
                    button.Enabled = false;
                }
                else
                {
                    this._bGuessSuccess = true;
                    this.button1.Enabled = true;

                    MessageBox.Show($"猜正确，用时{this.label_Time.Text}");

                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            RemoveButton();

            CreateButton();

            _bGuessSuccess = false;

            if (_Thread == null)
            {
                _Thread = new System.Threading.Thread(delegate ()
                {
                    int nCount = 0;

                    while (!_bGuessSuccess)
                    {
                        nCount = ++nCount > 10000000 ? 0 : nCount;

                        // 这种可能触发异常
                        //this.label_Time.Text = nCount.ToString();
                        /*
                         * 造成这种异常的原因在于，控件是在主线程中创建的（比如this.Controls.Add(...);)，
                         * 进入控件的事件响应函数时，是在控件所在的线程，并不是主线程。
                         * 在控件的事件响应函数中改变控件的状态，可能与主线程发生线程冲突。
                         * 如果主线程正在重绘控件外观，此时在别的线程改变控件外观，就会造成画面混乱。
                         * 不过这样的情况并不总会发生，如果主线程此时在重绘别的控件，就可能逃过一劫，
                         * 这样的写法可以正常通过，没有触发异常。
                         */

#if false   // C#3.0 以后
                        this.label_Time.Invoke(new Action(() =>
                        {
                            this.label_Time.Text = nCount.ToString();
                        }));

#else 
                        this.Invoke(new EventHandler(delegate
                        {
                            this.label_Time.Text = nCount.ToString();

                        }));
#endif

                        System.Threading.Thread.Sleep(1000);
                    }

                    this._Thread = null;
                });
            }

            _Thread.IsBackground = true;
            _Thread.Start();

            _nRandNum = new Random().Next(1, 100);
            this.button1.Enabled = false;
        }
    }
}
