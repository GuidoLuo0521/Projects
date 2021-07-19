using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._02_BasicApplication
{
    public partial class eg023_Typeof : Form
    {
        public eg023_Typeof()
        {
            InitializeComponent();
        }

        /*
         * typeof关键字用于获取类型的System.Type对象，通过System.Type对象调用相应的方法，可以得到类型中定义的成员。
         * 我们熟知的反射极值也用了类似的方式，使用反射机制首先向应用域中加载程序集，
         * 然后得到System.Type对象，然后通过System.Type对象中的成员信息来执行相应操作。
         */
        /*
         * 使用场景
         * 窗体内判定窗体类型，然后清空文本信息
         */
        private void button1_Click(object sender, EventArgs e)
        {
            Type type = typeof(Int64);

            foreach (MethodInfo item in type.GetMethods())
            {
                this.richTextBox1.ForeColor = Color.Red;
                this.richTextBox1.AppendText("方法名称：" + item.Name + Environment.NewLine);

                this.richTextBox1.ForeColor = Color.Black;
                foreach (ParameterInfo param in item.GetParameters())
                {
                    this.richTextBox1.AppendText("参数：" + param.Name + Environment.NewLine);
                }

                this.richTextBox1.AppendText(Environment.NewLine);
            }
        }

        private void Test()
        {
            foreach(Control item in Controls)
            {
                if(item.GetType() == typeof(TextBox))
                {
                    ((TextBox)item).Clear();
                }
            }
        }

    }
}
