using CSharp1200._02_BasicApplication;
using CSharp1200._03_StringProcessing;
using CSharp1200._05_GenericsClass;
using CSharp1200._07_WindowsBase;
using CSharp1200._08_SpecialForm;
using CSharp1200._09_ControlForm;
using CSharp1200._10_MDIForm;
using CSharp1200._11_Controls;
using CSharp1200._15_FileOpreate;
using CSharp1200._19_Office;
using CSharp1200._21_Graphics;
using CSharp1200._22_Image;
using CSharp1200.CSharp1200II;
using CSharp1200.CSharp1200II.IIChapter3;
using CSharp1200.CSharp1200II.IIChapter4;
using CSharp1200.CSharp1200II.IIChapter6;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200
{
    public partial class Form1 : Form
    {
        /// <summary>
        /// 主窗口主程序
        /// </summary>
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Chapter02 chapter02 = new Chapter02();
            chapter02.ShowDialog();
            chapter02.Dispose();
        }

        private void button03_Click(object sender, EventArgs e)
        {
            Chapter03 chapter03 = new Chapter03();
            chapter03.ShowDialog();
            chapter03.Dispose();
        }

        private void button05_Click(object sender, EventArgs e)
        {
            Chapter05 chapter05 = new Chapter05();
            chapter05.ShowDialog();
            chapter05.Dispose();
        }

        private void button07_Click(object sender, EventArgs e)
        {
            Chapter07 chapter07 = new Chapter07();
            chapter07.ShowDialog();
            chapter07.Dispose();
        }

        private void button08_Click(object sender, EventArgs e)
        {
            Chapter08 chapter08 = new Chapter08();
            chapter08.ShowDialog();
            chapter08.Dispose();
        }

        private void button09_Click(object sender, EventArgs e)
        {
            Chapter09 chapter09 = new Chapter09();
            chapter09.ShowDialog();
            chapter09.Dispose();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.ShowInTaskbar = true;
        }

        private void button10_Click(object sender, EventArgs e)
        {
            Chapter10 chapter10 = new Chapter10();
            chapter10.ShowDialog();
            chapter10.Dispose();
        }

        private void button11_Click(object sender, EventArgs e)
        {
            Chapter11 chapter11 = new Chapter11();
            chapter11.ShowDialog();
            chapter11.Dispose();
        }

        private void button15_Click(object sender, EventArgs e)
        {
            Chapter15 chapter15 = new Chapter15();
            chapter15.ShowDialog();
            chapter15.Dispose();
        }

        private void button19_Click(object sender, EventArgs e)
        {
            Chapter19 chapter19 = new Chapter19();
            chapter19.ShowDialog();
            chapter19.Dispose();
        }

        private void button21_Click(object sender, EventArgs e)
        {
            Chapter21 chapter21 = new Chapter21();
            chapter21.ShowDialog();
            chapter21.Dispose();
        }

        private void button22_Click(object sender, EventArgs e)
        {
            Chapter22 chapter22 = new Chapter22();
            chapter22.ShowDialog();
            chapter22.Dispose();
        }

        private void btnII001_Click(object sender, EventArgs e)
        {
            _1200II_Chapter1 form = new _1200II_Chapter1();
            form.ShowDialog();
            form.Dispose();
        }

        private void btnII003_Click(object sender, EventArgs e)
        {
            Chapter003 form = new Chapter003();
            form.ShowDialog();
            form.Dispose();
        }

        private void btnII004_Click(object sender, EventArgs e)
        {
            Chapter004 form = new Chapter004();
            form.ShowDialog();
            form.Dispose();
        }

        private void btnII006_Click(object sender, EventArgs e)
        {
            Chapter006 form = new Chapter006();
            form.ShowDialog();
            form.Dispose();
        }
    }
}
