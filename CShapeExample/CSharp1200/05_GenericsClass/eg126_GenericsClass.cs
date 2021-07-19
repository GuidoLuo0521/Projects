using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._05_GenericsClass
{
    public partial class eg126_GenericsClass : Form
    {
        public eg126_GenericsClass()
        {
            InitializeComponent();
        }

        

        private void button1_Click(object sender, EventArgs e)
        {
            GenericsClassTest<object> classTest = new _05_GenericsClass.GenericsClassTest<object>();

            classTest.Num = 10;
            classTest.Name = "Jhon";
            classTest.Age = 10;
            classTest.Birthday = DateTime.Now ;
            classTest.Salary = 15.6;

            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.Append("int:" + classTest.Num.ToString() + Environment.NewLine);
            stringBuilder.Append("string:" + classTest.Name.ToString() + Environment.NewLine);
            stringBuilder.Append("int:" + classTest.Age.ToString() + Environment.NewLine);
            stringBuilder.Append("datetime:" + classTest.Birthday.ToString() + Environment.NewLine);
            stringBuilder.Append("float:" + classTest.Salary.ToString() + Environment.NewLine);

            this.richTextBox1.Text = stringBuilder.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string[] roles = { "狼人", "预言家", "村民", "女巫", "丘比特", "猎人", "守卫\n" };
            this.richTextBox1.Text = Finder.Find<object>(roles, "预言家").ToString();
        }
    }


    // 泛型存储不同类型的数据列表
    public class GenericsClassTest<T>
    {
        public T Num;       // int
        public T Name;      // string 
        public T Age;       // int
        public T Birthday;  // DateTime
        public T Salary;    // float  

    }

    public class GenericsClassTest1<T> : GenericsClassTest<T>
    {
        public T Num1;       // int
        public T Name2;      // string 
    }

    public class Finder
    {
        public static int Find<T>(T[] items, T item)
        {
            for(int i = 0; i < items.Length; ++i)
            {
                if(item.Equals(items[i]))
                {
                    return i;
                }
            }

            return -1;
        }
    }

}
