using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200.CSharp1200II.IIChapter6
{
    public partial class Chapter006 : Form
    {
        public Chapter006()
        {
            InitializeComponent();
            TreeNode lastNode =  this.treeView1.Nodes[this.treeView1.Nodes.Count - 1];
            lastNode.Expand();

            lastNode.Nodes[lastNode.Nodes.Count - 1].Expand();
        }

        private DataTable GetData(string strQuery)
        {
            string strConnection = @"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Student.mdb";

            try
            {
                this.textBox1.Text = strQuery;

                DataTable dt = new DataTable();
                // 适合于连接任何类型的数据库
                using (OleDbDataAdapter da = new OleDbDataAdapter(strQuery, strConnection))
                {
                    da.Fill(dt);
                }
                return dt;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            return null;
        }

        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            switch (e.Node.Name)
            {
                case "128": NodeMouseClick_128(); break;
                case "129": NodeMouseClick_129(); break;
                case "130": NodeMouseClick_130(); break;
                case "131": NodeMouseClick_131(); break;
                case "132": NodeMouseClick_132(); break;
                case "133": NodeMouseClick_133(); break;
                case "134": NodeMouseClick_134(); break;
                case "135": NodeMouseClick_135(); break;
                case "136": NodeMouseClick_136(); break;
                case "137": NodeMouseClick_137(); break;
                case "138": NodeMouseClick_138(); break;
                case "139": NodeMouseClick_139(); break;
                case "140": NodeMouseClick_140(); break;
                case "141": NodeMouseClick_141(); break;
                case "142": NodeMouseClick_142(); break;
                case "143": NodeMouseClick_143(); break;
                case "144": NodeMouseClick_144(); break;
                case "145": NodeMouseClick_145(); break;
                case "146": NodeMouseClick_146(); break;
                case "147": NodeMouseClick_147(); break;
                case "148": NodeMouseClick_148(); break;
                case "149": NodeMouseClick_149(); break;
                case "150": NodeMouseClick_150(); break;
                case "151": NodeMouseClick_151(); break;
                case "152": NodeMouseClick_152(); break;
                case "153": NodeMouseClick_153(); break;
                case "154": NodeMouseClick_154(); break;
                case "155": NodeMouseClick_155(); break;
                case "156": NodeMouseClick_156(); break;
                case "157": NodeMouseClick_157(); break;
                case "158": NodeMouseClick_158(); break;
                case "159": NodeMouseClick_159(); break;
                case "160": NodeMouseClick_160(); break;
                case "161": NodeMouseClick_161(); break;
                case "162": NodeMouseClick_162(); break;
                case "163": NodeMouseClick_163(); break;
                case "164": NodeMouseClick_164(); break;
                case "165": NodeMouseClick_165(); break;
                case "166": NodeMouseClick_166(); break;
                case "167": NodeMouseClick_167(); break;
                case "168": NodeMouseClick_168(); break;
                case "169": NodeMouseClick_169(); break;
                case "170": NodeMouseClick_170(); break;
                case "171": NodeMouseClick_171(); break;
                case "172": NodeMouseClick_172(); break;
                case "176": NodeMouseClick_176(); break;

            }
        }

        private void NodeMouseClick_176()
        {
            // 数据分组统计（单列）
            // GROUP BY 对指定数据列的信息进行分组，
            string strQuery = $"SELECT 年龄, SUM(年龄) AS 总年龄 FROM StudentInfo GROUP BY 年龄,家庭住址";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_172()
        {
            // 列出数据中的重复记录和记录条数
            // GROUP BY 分组
            // HAVING 对分组信息设置查询条件
            string strQuery = $"SELECT 语文, COUNT(语文) AS 条数 FROM Grade GROUP BY 语文 HAVING COUNT(语文)=2";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_171()
        {
            // 查询时不显示重复记录
            //DISTINCT
            string strQuery = $"SELECT DISTINCT 语文 FROM Grade";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_170()
        {
            // NOT与谓词进行组合条件的查询
            // Colume NOT BETWEEN --- AND ---
            string strQuery = $"SELECT * FROM Grade WHERE 高数 > 50 AND 语文 NOT BETWEEN 100 AND 60";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_169()
        {
            // 利用运算符查询指定条件的数据
            string strQuery = $"SELECT * FROM StudentInfo WHERE 学生姓名 LIKE '李%' ";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_168()
        {
            // 查询指定时间间隔的数据
            // https://support.microsoft.com/zh-cn/office/datediff-%E5%87%BD%E6%95%B0-e6dd7ee6-3d01-4531-905c-e24fc238f85f
            string strQuery = @"SELECT *,DATEDIFF('yyyy',出生日期,Date()) AS 年龄 FROM StudentInfo ORDER BY ID";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_167()
        {
            // 返回当前日期时间及其对应的星期
            string strQuery = $"SELECT *, Date() AS 当前日期, Weekday(出生日期) AS 星期 FROM StudentInfo ORDER BY ID" ;
            this.dataGridView1.DataSource = GetData(strQuery);

        }

        private void NodeMouseClick_166()
        {
            // 按年、月或日查询数据 
            // AND MONTH(出生日期) = '9' AND DAY(出生日期) = '3';
            string strQuery = $"SELECT * FROM StudentInfo WHERE YEAR(出生日期) = '2020' ";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_165()
        {
            // 指定时间段
            // 指定范围
            string strQuery = $"SELECT * FROM StudentInfo WHERE 出生日期 BETWEEN #2020/3/9# AND #2021/3/9#";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_164()
        {
            // 指定日期数据
            string strQuery = $"SELECT * FROM StudentInfo WHERE 出生日期 = #2021/3/9#";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_163()
        {
            //判断是否为日期
            string strQuery = 
                $"SELECT *, " +
                $"IIF(ISDATE(出生日期), '是', '不是')" + 
                $"AS 是否为日期 " +
                $"FROM StudentInfo";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_162()
        {
            // 比较两个字符串
        }

        private void NodeMouseClick_161()
        {
            // 查找并替换字符串
        }

        private void NodeMouseClick_160()
        {
            // 删除字符串中的子串
        }

        private void NodeMouseClick_159()
        {
            // 返回字符串中的子串
        }

        private void NodeMouseClick_158()
        {
            // 返回字符在字符串中出现的次数
            // 

        }

        private void NodeMouseClick_157()
        {
            // 实现字符串的大小写转换
            // LCase() 小写
            // UCase() 大写
            string strQuery = @"SELECT 英文名字 AS 原名, LCase(英文名字) AS 小写, UCase(英文名字) AS 大写 FROM StudentInfo";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_156()
        {
            // 根据查询数值的符号显示具体文本
            string strQuery = @"SELECT *, IIF(语文>= 60,'及格','不及格') AS 语文成绩 FROM Grade";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_155()
        {
            // 根据生成的随机数查询记录 
            // Int((upperbound - lowerbound + 1) * Rnd + lowerbound)
            string strQuery = "SELECT * FROM StudentInfo WHERE ID = Int((20 - 10 + 1) * Rnd(1) + 10)";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_154()
        {
            //  求数值的绝对值
            string strQuery = "SELECT 语文 AS 数值取整前, ABS(语文) AS 绝对值 FROM Grade";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_153()
        {
            // 使用三角函数计算数值 
            string strQuery = "SELECT 语文 AS 数值取整前, SIN(语文 * Pi() / 180) AS 正弦值 FROM Grade";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_152()
        {
            // 将查询到的数值四舍五入
            string strQuery = "SELECT 语文 AS 数值取整前, ROUND(语文) AS 数值取整后 FROM Grade";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_151()
        {
            // 在查询时对数值进行取整
            // ACCSSS FIX()
            // FIX() 上取整 
            string strQuery = "SELECT 语文 AS 数值取整前, FIX(语文) AS 数值取整后 FROM Grade";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_150()
        {
            // 判断是否为数值
            // ISNUMERIC() 函数
            string strQuery = $"Select 学生编号 as 编号,学生姓名 as 姓名,IsNumeric(出生日期)=1 FROM StudentInfo";
            this.dataGridView1.DataSource = GetData(strQuery);

            // 如果不行，就自己填充
            // foreach()
        }

        private void NodeMouseClick_149()
        {
            // 查询 后20%  ASC顺序排列
            string strQuery = $"Select TOP 20 PERCENT * " +
                    $"FROM GRADE ORDER BY 总分 ASC";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_148()
        {
            // 查询 前50% 逆序排序
            string strQuery = $"Select TOP 50 PERCENT * " +
                    $"FROM GRADE ORDER BY 总分 DESC";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_147()
        {
            // 查询第10到第20名的数据 
            // 子查询 先查 20个，在排序，在查10个

           string strQuery = $"Select TOP 10 * FROM (SELECT TOP 20 * FROM GRADE ORDER BY 总分 DESC) ORDER BY 总分 ASC";
           this.dataGridView1.DataSource = GetData(strQuery);

        }

        private void NodeMouseClick_146()
        {
            // 取出数据统计结果的后10名数据
            // 倒叙排序
            string strQuery = $"Select TOP 10 * " +
                    $"FROM StudentInfo ORDER BY ID DESC";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_145()
        {
            // 查询前10名数据
            string strQuery = $"Select TOP 10 * " +
                    $"FROM StudentInfo ";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_144()
        {
            // 复杂的模糊查询
            string strQuery = $"Select * " +
                    $"FROM StudentInfo WHERE 学生姓名 NOT LIKE '[张李]%' AND 年龄 > 20";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_143()
        {
            // 利用“[^]”通配符进行查询
            // 匹配非[]内的字符
            // 还是使用了 NOT LIKE
            string strQuery = $"Select * " +
                    $"FROM StudentInfo WHERE 学生姓名 NOT LIKE '[张李]%'";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_142()
        {
            // 利用“[]”通配符进行查询
            // 代表方括号范围内的单个字符
            string strQuery = $"Select * " +
                    $"FROM StudentInfo WHERE 学生姓名 LIKE '%[张李]%'";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_141()
        {
            // 利用“%”通配符进行查询
            // 匹配一个或多个
            string strQuery = $"Select * " +
                    $"FROM StudentInfo WHERE 学生姓名 LIKE '张%'";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_140()
        {
            // 利用“_”通配符进行查询
            // 匹配一个
            string strQuery = $"Select * " +
                $"FROM StudentInfo WHERE 学生姓名 LIKE '张_'";
            this.dataGridView1.DataSource = GetData(strQuery);

        }

        private void NodeMouseClick_139()
        {
            // 利用日期数据变量查询字符串数据
            string strQuery = $"Select 学生编号 as 编号,学生姓名 as 姓名,出生日期 " +
                $"FROM StudentInfo WHERE 出生日期 =#{this.dateTimePicker1.Text}#";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_138()
        {
            // 利用数值型数据变量查询字符串数据
            if (this.tbAge.Text == "")
            {
                MessageBox.Show("年龄为空~");
                return;
            }

                string strQuery = $"Select * FROM StudentInfo WHERE 年龄 = {(int.Parse(this.tbAge.Text)).ToString()}";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_137()
        {
            // 利用变量查询字符串数据
            if (this.tbStudentName.Text == "")
            {
                MessageBox.Show("姓名为空~");
                return;
            }

            string strQuery = $"Select * FROM StudentInfo WHERE 学生姓名 = '{this.tbStudentName.Text}'";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_136()
        {
            // 查询空（‘’或NULL）数据
            string strQuery = $"Select 学生编号 as 编号,学生姓名 as 姓名,统招,家庭住址 FROM StudentInfo WHERE 家庭住址 IS NULL OR 家庭住址 = ''";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_135()
        {
            // 查询日期  ## 包含起来  
            string strQuery = $"Select 学生编号 as 编号,学生姓名 as 姓名,统招 FROM StudentInfo WHERE 统招 = TRUE";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_134()
        {
            // 查询日期  ## 包含起来  
            string strQuery = $"Select 学生编号 as 编号,学生姓名 as 姓名,出生日期 FROM StudentInfo WHERE 出生日期 =#2021/3/19#";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_133()
        {
            // 查询文字  单引号 包含起来   ''
            string strQuery = @"Select 学生编号 as 编号,学生姓名 as 姓名 FROM StudentInfo WHERE 学生姓名 = '张三'";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_132()
        {
            // 查询数字
            string strQuery = @"Select 学生编号 as 编号,学生姓名 as 姓名 FROM StudentInfo WHERE 年龄 = 18";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_131()
        {
            // 使用函数设置条件
            // 使用 WHERE 对查询设置条件
            // LEN() 获取长度
            string strQuery = @"Select 学生编号 as 编号,学生姓名 as 姓名 FROM StudentInfo WHERE LEN(学生姓名) = 2";
            this.dataGridView1.DataSource = GetData(strQuery);

        }

        private void NodeMouseClick_130()
        {
            // 在列上加入计算
            // 列上加上计算后，数据列是没有名称的。用AS关键字或空格为该数据列设置别名
            string strQuery = @"Select 学生编号 as 编号,学生姓名 as 姓名,外语 + 高数 as 外语加高数 FROM Grade";
            this.dataGridView1.DataSource = GetData(strQuery);
        }

        private void NodeMouseClick_129()
        {
            // 使用别名
            string strQuery = @"Select 学生编号 as 编号,学生姓名 as 姓名,性别,年龄,家庭住址 FROM StudentInfo";
            this.dataGridView1.DataSource = GetData(strQuery);
        }


        private void NodeMouseClick_128()
        {
            string strQuery = @"Select 学生编号,学生姓名,性别,年龄,家庭住址 FROM StudentInfo";
            this.dataGridView1.DataSource = GetData(strQuery);
        }
    }
}

