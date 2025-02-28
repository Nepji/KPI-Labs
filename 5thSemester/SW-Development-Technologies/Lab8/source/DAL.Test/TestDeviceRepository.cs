using DAL.Entities;
using DAL.Repositories.Impl;
using Microsoft.EntityFrameworkCore;

namespace Test
{
    public class TestDeviceRepository : BaseRepository<Device>
    {
        public TestDeviceRepository(DbContext context) : base(context)
        {
            
        }
    }
}