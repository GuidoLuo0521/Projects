using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._09_ControlForm
{
    public partial class eg200_DragImageToForm : Form
    {
        public eg200_DragImageToForm()
        {
            InitializeComponent();
        }

        private void eg200_DragImageToForm_DragDrop(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                string[] rs = (string[])e.Data.GetData(DataFormats.FileDrop);

                this.textBox1.Text = rs[0];
                this.pictureBox1.Load(rs[0]);//加载对应路径的图片
            }
        }

        private void eg200_DragImageToForm_DragEnter(object sender, DragEventArgs e)
        {

            if (e.Data.GetDataPresent(DataFormats.FileDrop))
                e.Effect = DragDropEffects.All;                                                              //重要代码：表明是所有类型的数据，比如文件路径
            else
                e.Effect = DragDropEffects.None;
        }
    }
}
