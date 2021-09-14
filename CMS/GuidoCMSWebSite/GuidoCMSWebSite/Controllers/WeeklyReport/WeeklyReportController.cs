using GuidoCMS.Model;
using Microsoft.AspNetCore.Mvc;
using MySql.Data.MySqlClient;
using Newtonsoft.Json;
using System;
using System.IO;
using System.Text;

namespace GuidoCMS.Controllers
{

    [ApiController]
    [Route("[controller]")]

    public class WeeklyReportController : ControllerBase
    {

        static private string _ConnectionString = "server=www.millet.fun;User Id=guido;password=123456;Database=GuidoCMS";

        /// <summary> 
        /// DataReader转换为Json 
        /// </summary> 
        /// <param name="dataReader">DataReader对象</param> 
        /// <returns>Json字符串</returns> 
        public static string ToJson(MySqlDataReader dataReader)
        {
            StringBuilder jsonString = new StringBuilder();
            jsonString.Append("[");
            while (dataReader.Read())
            {
                jsonString.Append("{");
                for (int i = 0; i < dataReader.FieldCount; i++)
                {
                    Type type = dataReader.GetFieldType(i);
                    string strKey = dataReader.GetName(i);
                    string strValue = dataReader[i].ToString();
                    jsonString.Append("\"" + strKey + "\":");
                    strValue = String.Format(strValue, type);
                    if (i < dataReader.FieldCount - 1)
                    {
                        jsonString.Append($"\"{strValue}\"" + ",");
                    }
                    else
                    {
                        jsonString.Append($"\"{strValue}\"");
                    }
                }
                jsonString.Append("},");
            }
            dataReader.Close();
            jsonString.Remove(jsonString.Length - 1, 1);
            jsonString.Append("]");
            return jsonString.ToString();
        }



        [HttpPost]
        public void Post(WeeklyReportFileModel entity)
        {
            var jsonStr = JsonConvert.SerializeObject(entity).ToString();
            string year = DateTime.Now.Year.ToString();

            string strDir = $"C:/GuidoCMS/{entity.StaffID}/WeeklyReport/{year}/";
            Directory.CreateDirectory(strDir);
            string strPath = strDir + entity.FileName;

            using (StreamWriter sw = new StreamWriter(strPath))
            {
                sw.Write(jsonStr);
                sw.Flush();
                sw.Close();
            }

            string strTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            string strQuery =   $"INSERT INTO weeklyreport(StaffID, FileName, WeekNumber, CommitDate, " +
                                $"CommitIP, CommitMac, RelatetivePath, Project, Finished, Plan) " +
                                $"VALUES('{entity.StaffID}', '{entity.FileName}', '{entity.WeekNumber}', '{strTime}', '{entity.IP}', '{entity.MAC}', '{strDir}'," +
                                $"'{entity.Project}', '{entity.Finished}', '{entity.Plan}')";

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
        public string Get(string staffid)
        {
            if (staffid == null || staffid == "")
                return "{}";

            string strQuery = $"select w.* from weeklyreport w where (w.staffid, w.WeekNumber, w.CommitDate) in " +
                $"(select wr.staffid, wr.WeekNumber, max(wr.CommitDate)  " +
                $"  from weeklyreport wr where staffid = '{staffid}' " +
                $"  group by wr.staffid, wr.WeekNumber) " +
                $"order by w.WeekNumber DESC";

            using (MySqlConnection con = new MySql.Data.MySqlClient.MySqlConnection(_ConnectionString))
            {
                try
                {
                    StringBuilder jsonString = new StringBuilder();
                    jsonString.Append("{ ");

                    con.Open();

                    MySqlCommand mycmd1 = new MySqlCommand(strQuery, con);
                    MySqlDataReader reader = mycmd1.ExecuteReader();
                    while (reader.Read())
                    {
                        
                        jsonString.Append($"\"{reader["WeekNumber"].ToString()}\":{{");
                        jsonString.Append($"\"ReportID\":\"{reader["ReportID"].ToString()}\",");
                        jsonString.Append($"\"CommitDate\":\"{Convert.ToDateTime(reader["CommitDate"].ToString()).ToString("yyyy-MM-d HH:mm:ss")}\",");
                        jsonString.Append($"\"Project\":\"{reader["Project"].ToString()}\",");
                        jsonString.Append($"\"Finished\":\"{reader["Finished"].ToString()}\",");
                        jsonString.Append($"\"Plan\":\"{reader["Plan"].ToString()}\"");

                        jsonString.Append("},");
                    }
                    reader.Close();
                    jsonString.Remove(jsonString.Length - 1, 1);
                    jsonString.Append("}");

                    con.Close();
                    return jsonString.ToString();
                }
                catch
                {
                    return "{}";
                }
            }
        }
    }
}
