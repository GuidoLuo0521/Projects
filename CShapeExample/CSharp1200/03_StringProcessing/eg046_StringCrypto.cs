using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp1200._03_StringProcessing
{
    public partial class eg046_StringCrypto : Form
    {

        public eg046_StringCrypto()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 加密
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            
        }

        private void button2_Click(object sender, EventArgs e)
        {

        }
    }


    public class Encrypt
    {
        /// <summary>
        /// 加密
        /// </summary>
        /// <param name="encryptKey">密钥</param>
        /// <param name="str">信息</param>
        /// <returns></returns>
        internal string ToEncrypt(string encryptKey, string str)
        {
            try
            {
                byte[] P_byte_key = //将密钥字符串转换为字节序列
                    Encoding.Unicode.GetBytes(encryptKey);
                byte[] P_byte_data = //将字符串转换为字节序列
                    Encoding.Unicode.GetBytes(str);
                MemoryStream P_Stream_MS = //创建内存流对象
                    new MemoryStream();
                CryptoStream P_CryptStream_Stream = //创建加密流对象
                    new CryptoStream(P_Stream_MS, new DESCryptoServiceProvider().
                   CreateEncryptor(P_byte_key, P_byte_key), CryptoStreamMode.Write);

                P_CryptStream_Stream.Write(//向加密流中写入字节序列
                    P_byte_data, 0, P_byte_data.Length);
                P_CryptStream_Stream.FlushFinalBlock();//将数据压入基础流,用缓冲区的当前状态更新基础数据源或储存库，随后清除缓冲区。
                byte[] P_bt_temp =//从内存流中获取字节序列
                    P_Stream_MS.ToArray();
                P_CryptStream_Stream.Close();//关闭加密流
                P_Stream_MS.Close();//关闭内存流
                return //方法返回加密后的字符串
                    Convert.ToBase64String(P_bt_temp);
            }
            catch (CryptographicException ce)
            {
                throw new Exception(ce.Message);
            }
        }

        internal string ToDecrypt(string encryptKey, string str)
        {
            try
            {
                byte[] P_byte_key = //将密钥字符串转换为字节序列
                    Encoding.Unicode.GetBytes(encryptKey);
                byte[] P_byte_data = //将加密后的字符串转换为字节序列
                    Convert.FromBase64String(str);
                MemoryStream P_Stream_MS =//创建内存流对象并写入数据
                    new MemoryStream(P_byte_data);
                CryptoStream P_CryptStream_Stream = //创建加密流对象
                    new CryptoStream(P_Stream_MS, new DESCryptoServiceProvider().
                    CreateDecryptor(P_byte_key, P_byte_key), CryptoStreamMode.Read);

                byte[] P_bt_temp = new byte[200];//创建字节序列对象

                MemoryStream P_MemoryStream_temp =//创建内存流对象
                    new MemoryStream();
                int i = 0;//创建记数器
                while ((i = P_CryptStream_Stream.Read(//使用while循环得到解密数据
                    P_bt_temp, 0, P_bt_temp.Length)) > 0)//(1\从当前流中读取200个字节-并将它们存储在 P_bt_temp 中 2\P_bt_temp 中的字节偏移量-从该偏移量开始存储从当前流中读取的数据 3\读入缓冲区中的总字节数)
                {
                    P_MemoryStream_temp.Write(//将解密后的数据放入内存流
                        P_bt_temp, 0, i);
                }
                return //方法返回解密后的字符串
                    Encoding.Unicode.GetString(P_MemoryStream_temp.ToArray());
            }
            catch (CryptographicException ce)
            {
                throw new Exception(ce.Message);
            }
        }
    }
}
