using System;
using System.Collections.Generic;

namespace DAL.Entities
{
    public class Device
    {
        public int DeviceId { get; set; }
        public String Mark { get; set; }
        public IEnumerable<Users> InstalledById { get; set; }
    }
}