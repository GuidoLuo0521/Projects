using GuidoCMS.Model;
using Microsoft.AspNetCore.Mvc;
using MySql.Data.MySqlClient;
using Newtonsoft.Json;
using System;
using System.IO;

namespace GuidoCMS.Controllers
{

    [ApiController]
    [Route("[controller]")]

    public class WeeklyReportController : ControllerBase
    {

        static private string _ConnectionString = "server=www.millet.fun;User Id=guido;password=123456;Database=GuidoCMS";

        [HttpPost]
        public void Post(string staffid, string year, string weeknumber, WeeklyReportFileModel entity)
        {
            var jsonStr = JsonConvert.SerializeObject(entity).ToString();

            string strDir = $"C:/GuidoCMS/{staffid}/WeeklyReport/{year}/";
            Directory.CreateDirectory(strDir);
            string strPath = strDir + entity.FileName;

            using (StreamWriter sw = new StreamWriter(strPath))
            {
                sw.Write(jsonStr);
                sw.Flush();
                sw.Close();
            }

            string strTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:dd");
            string strQuery = $"INSERT INTO weeklyreport(StaffID, FileName, WeekNumber, CommitDate, CommitIP, CommitMac, RelatetivePath) " +
                              $"VALUES('{staffid}', '{entity.FileName}', '{weeknumber}', '{strTime}', '{entity.IP}', '{entity.MAC}', '{strDir}')";

            using (MySqlConnection con = new MySql.Data.MySqlClient.MySqlConnection(_ConnectionString))
            {
                try
                {
                    con.Open();

                    MySqlCommand mycmd1 = new MySqlCommand(strQuery, con);
                    mycmd1.ExecuteNonQuery();

                    //MySqlDataReader reader = mycmd1.ExecuteReader();
                    con.Close();

                    return;
                }
                catch
                {
                    return;
                }
            }

        }

        [HttpGet]
        public string  Get()
        {
            string strYear = DateTime.Now.ToString("yyyy");

            string strQuery = $"SELECT * FROM `weeklyreport` WHERE commitdate > '{strYear}-00-00 00:00:00'";

            string str = "";
            using (MySqlConnection con = new MySql.Data.MySqlClient.MySqlConnection(_ConnectionString))
            {
                try
                {
                    con.Open();

                    MySqlCommand mycmd1 = new MySqlCommand(strQuery, con);
                    mycmd1.ExecuteNonQuery();

                    MySqlDataReader reader = mycmd1.ExecuteReader();
                    
                    while(reader.Read())
                    {
                        str += reader["FileName"].ToString();
                    }

                    con.Close();
                    return str;
                }
                catch
                {
                    return "";
                }
            }
        }
    }
}
