using DAL.Entities;
using Microsoft.EntityFrameworkCore;

namespace DAL.EF
{
    public class DeviceNZoneContext : DbContext
    {
        public System.Data.Entity.DbSet<Device> Devices { get; set; }
        public System.Data.Entity.DbSet<DeviceZone> DeviceZozes { get; set; }

        public DeviceNZoneContext(DbContextOptions options) : base(options)
        {
        }
    }
}