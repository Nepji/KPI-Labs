using DAL.EF;
using DAL.Entities;
using DAL.Repositories.Interfaces;

namespace DAL.Repositories.Impl
{
    public class DeviceRepository : BaseRepository<Device>, IDeviceRepository
    {
        internal DeviceRepository(DeviceNZoneContext context) : base (context)
        {
            
        }
    }
}