using CSharp1200.Properties;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._22_Image
{
    public partial class Chapter22 : Form
    {
        public Chapter22()
        {
            InitializeComponent();
        }

        bool _bMouseDown = false;
        

        private void btnChoose_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.InitialDirectory = Application.StartupPath;
            fileDialog.Filter = "bmp(*.bmp)|*.bmp|png(*.png)|*.png|all(*.*)|*.*";
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                this.textBox1.Text = fileDialog.FileName;
                string strName = Path.GetFileNameWithoutExtension(fileDialog.FileName);
                string strSaveJpeg = Path.GetDirectoryName(fileDialog.FileName) + $"\\{strName}.jpeg";
                Image image = Image.FromFile(fileDialog.FileName);

                /*
                 *         //
                    public static ImageFormat MemoryBmp => memoryBMP;
                    public static ImageFormat Bmp => bmp;
                    public static ImageFormat Emf => emf;
                    public static ImageFormat Wmf => wmf;
                    public static ImageFormat Gif => gif;
                    public static ImageFormat Jpeg => jpeg;
                    public static ImageFormat Png => png;
                    public static ImageFormat Tiff => tiff;
                    public static ImageFormat Exif => exif;
                    public static ImageFormat Icon => icon;
                 */
                image.Save(strSaveJpeg, ImageFormat.Jpeg);

                MessageBox.Show("已保存");
            }
        }

        int xPos;
        int yPos;
        int lastx, lasty;

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            try
            {
                if(_bMouseDown)
                {
                    /**********************************************/
                    int x = System.Math.Abs(lastx - e.X);     //  改
                    int y = System.Math.Abs(lasty - e.Y);     //  进
                    double dis = Math.Sqrt(x * x + y * y);    //  部
                    if (dis > 3)                              //  分
                    {
                        /**********************************************/
                        this.pictureBox1.Left += Convert.ToInt32(e.X - xPos);//设置x坐标.
                        this.pictureBox1.Top += Convert.ToInt32(e.Y - yPos);//设置y坐标.
                        lastx = e.X;
                        lasty = e.Y;
                    }

                    Graphics g = this.pictureBox1.CreateGraphics();
                    g.DrawImage(Resources.TestPic, new Point(0, 0));
                }
                else
                {
                    Graphics g = this.pictureBox1.CreateGraphics();

                    g.DrawImage(Resources.TestPic, new Point(0, 0));
                    Rectangle srcRect = new Rectangle(e.X, e.Y, 20, 20);
                    Rectangle dstRect = new Rectangle(e.X, e.Y, 80, 80);

                    g.DrawImage(this.pictureBox1.Image, dstRect, srcRect, GraphicsUnit.Pixel);
                }
            }
            catch
            {

            }
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            _bMouseDown = true;
            xPos = e.X;//当前x坐标.
            yPos = e.Y;//当前y坐标.
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            _bMouseDown = false;
            
        }
    }
}
