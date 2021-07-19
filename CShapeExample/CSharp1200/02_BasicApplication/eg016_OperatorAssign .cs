using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp1200._02_BasicApplication
{
    /*
     * 字符串是一系列Unicode字符组成的集合，如转义序列 “\u0022”是字符串的一个元素 表示“\"”
     */

    class eg016_OperatorAssign
    {
        /// <summary>
        /// 测试
        /// </summary>
        static public void eg016_OperatorAssign_Main()
        {
            Test_String();
            
            Test_Transferred();

            Console.ReadLine();
        }

        static public void SplitFun()
        {
            Console.WriteLine("---------------------------------------");
        }

        /// <summary>
        /// 字符赋值测试
        /// </summary>
        static public void Test_String()
        {
            // Console.WriteLine(new StackTrace(true).ToString());

            // "@"防止转义
            string str0 = @"c:\bin";
            Console.WriteLine(str0);

            string str1 = "c:\\bin";
            Console.WriteLine(str1);

            SplitFun();
        }

        static public void Test_Transferred()
        {
            // Console.WriteLine(new StackTrace(true).ToString());

            string str = "\"";
            string str_01, str_02, str_03;
            str_01 = "Hello,\"C#\"";
            str_02 = "Hello," + "\u0022" + "C#" + "\u0022";
            str_03 = "Hello," + str + "C#" + "\u0022";

            Console.WriteLine(str_01);
            Console.WriteLine(str_02);
            Console.WriteLine(str_03);

            SplitFun();
        }

    }
}
