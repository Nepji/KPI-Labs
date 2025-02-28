using DAL.EF;
using DAL.Entities;
using DAL.Repositories.Interfaces;

namespace DAL.Repositories.Impl
{
    public class DeviceZoneRepository : BaseRepository<DeviceZone>, IDeviceZoneRepository
    {
        internal DeviceZoneRepository(DeviceNZoneContext context) : base (context)
        {
            
        }
    }
}