using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._21_Graphics
{
    public partial class Chapter21 : Form
    {
        public Chapter21()
        {
            InitializeComponent();
        }

        private void btnDrawLine_Click(object sender, EventArgs e)
        {
            Graphics g = this.panel1.CreateGraphics();
            g.DrawLine(new Pen(Color.Red), 10, 10, 10, 20);

            // 左上角  宽高
            g.DrawRectangle(new Pen(Color.Blue), 20, 10, 30, 30);
            g.DrawEllipse(new Pen(Color.Blue), 50, 10, 30, 30);

            // X轴为起点，顺时针
            g.DrawArc(new Pen(Color.Blue), 80, 10, 30, 30, 0, 40);

            // X轴为起点，顺时针
            g.DrawPie(new Pen(Color.Blue), 100, 10, 30, 30, 0, 40);
        }

        private void btnOfficialStamp_Click(object sender, EventArgs e)
        {
            Graphics g = this.panel1.CreateGraphics();
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            int nLeftx = 100;
            int nTop = 100 ;

            int nWidth = 200;
            int nHeight = 200;

            Pen pen = new Pen(Color.Blue, 10);
            g.DrawEllipse(pen, nLeftx, nTop, nWidth, nHeight);

            string strCompany = "重庆康如来有限公司";
            int nLen = strCompany.Length;
            float fAngle = 180 + (180 - nLen * 20) / 2;
            for(int i = 0; i < nLen; ++i)
            {
                g.TranslateTransform(nLeftx + nWidth / 2, nTop + nHeight / 2);
                g.RotateTransform(fAngle);
                g.DrawString(strCompany[i].ToString(), this.Font, new SolidBrush(Color.Red), -100+20, 0);
                g.ResetTransform();
                fAngle += 20;
            }

        }

        /// <summary>
        /// 双缓冲绘图 
        /// 创建一个Bitmap，调用Graphics类的FromImage创建画布，调用Graphics.DrawImage()
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDoubleBuffer_Click(object sender, EventArgs e)
        {
            // 先建一张位图
            Bitmap bitmap = new Bitmap(this.panel1.Width, this.panel1.Height);
            // 位图选进画布
            Graphics g = Graphics.FromImage(bitmap);
            // 绘制
            g.FillEllipse(new SolidBrush(Color.DarkMagenta), this.panel1.Bounds);
            // 控件创建画布
            Graphics gPanel = this.panel1.CreateGraphics();
            // 位图绘制到控件画布上
            gPanel.DrawImage(bitmap, 20, 10);
            // 释放资源
            bitmap.Dispose();
            g.Dispose();
            gPanel.Dispose();

        }
    }
}
