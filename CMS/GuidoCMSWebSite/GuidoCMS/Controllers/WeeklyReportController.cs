using GuidoCMS.Model;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;

namespace GuidoCMS.Controllers
{

    [ApiController]
    [Route("[controller]")]

    public class WeeklyReportController : ControllerBase
    {
        [HttpPost]
        public void Post(string staffid, string year, string weeknumber, WeeklyReportFileModel entity)
        {
            var jsonStr = JsonConvert.SerializeObject(entity).ToString();

            string strDir = $"F:/GuidoCMS/{staffid}/WeeklyReport/{year}/";
            Directory.CreateDirectory(strDir);
            string strPath = strDir + entity.FileName;

            using (StreamWriter sw = new StreamWriter(strPath))
            {
                sw.Write(jsonStr);
                sw.Flush();
                sw.Close();
            }
        }

        [HttpGet]
        public string Get()
        {
            return "WeeklyReportController::Get()";
        }
    }
}
