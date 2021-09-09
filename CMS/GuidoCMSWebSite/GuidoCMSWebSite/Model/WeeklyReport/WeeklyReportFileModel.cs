using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GuidoCMS.Model
{
    public class WeeklyReportFileModel
    {
        public string StaffID { get; set; }
        public string FileName { get; set; }
        public string Date { get; set; }
        public string WeekNumber { get; set; }
        public string IP { get; set; }
        public string MAC { get; set; }
        public string Project { get; set; }
        public string Finished { get; set; }
        public string Plan { get; set; }
    }
}
