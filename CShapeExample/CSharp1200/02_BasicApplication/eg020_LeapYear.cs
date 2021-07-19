using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._02_BasicApplication
{
    /// <summary>
    /// 闰年判定
    /// </summary>
    public partial class eg020_LeapYear : Form
    {
        /*
         * 闰年为了弥补认为历法规定造成的每一年的天数与地球实际公转周期的时间差而设定的，补上时间差的年份
         * 闰年共366天
         * 四年一闰，百年不闰，四百年再闰
         * 算法：能被400整除，或能整除4不能整除100
         */

        public eg020_LeapYear()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int nInput = int.Parse(this.tbInput.Text);

            this.lbResult.Text = (nInput % 400 == 0 || (nInput % 4 == 0) && (nInput % 100 != 0)) ? $"{nInput}:是闰年" : $"{nInput}:不是闰年";
        }
    }
}
