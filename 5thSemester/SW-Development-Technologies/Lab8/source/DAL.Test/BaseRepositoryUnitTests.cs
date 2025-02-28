using DAL.EF;
using DAL.Entities;
using Microsoft.EntityFrameworkCore;
using Moq;
using Xunit;

namespace Test
{
    public class BaseRepositoryUnitTests
    {
        [Fact]
        public void Create_InputDeviceInstance_CallsAddMethodOfDbSetWithStreetInstance()
        {
        //Arrange
            DbContextOptions<DeviceNZoneContext> options = new DbContextOptionsBuilder<DeviceNZoneContext>().Options;
            var mockContext = new Mock<DeviceNZoneContext>(options);
            var mockDbSet = new Mock<DbSet<Device>>();
            mockContext.Setup(context => context.Set<Device>()).Returns(mockDbSet.Object);
            var repository = new TestDeviceRepository(mockContext.Object);
            Device expectedDevice = new Mock<Device>().Object;
            
        //Act
        repository.Create(expectedDevice);
        
        //Assert
        mockDbSet.Verify(dbSet => dbSet.Add(expectedDevice), Times.Once);
        }

        [Fact]
        public void Get_byInputId_CallsFindMethodOfDb()
        {
            //Arrange
            DbContextOptions<DeviceNZoneContext> options = new DbContextOptionsBuilder<DeviceNZoneContext>().Options;
            var mockContext = new Mock<DeviceNZoneContext>(options);
            var mockDbSet = new Mock<DbSet<Device>>();
            mockContext.Setup(context => context.Set<Device>()).Returns(mockDbSet.Object);
            Device expectedDevice = new Device { DeviceId = 1};
            mockDbSet.Setup(mock => mock.Find(expectedDevice.DeviceId)).Returns(expectedDevice);
            var repository = new TestDeviceRepository(mockContext.Object);
            
            //Act
            var currentDevice = repository.Get(expectedDevice.DeviceId);
            
            //Assert
            mockDbSet.Verify(DbSet => DbSet.Find(expectedDevice.DeviceId),Times.Once);
            Assert.Equal(expectedDevice,currentDevice);
        }

        [Fact]
        public void Delete_byInputId_CallsFindNRemoveMethodOfDb()
        {
            //Arrange
            DbContextOptions<DeviceNZoneContext> options = new DbContextOptionsBuilder<DeviceNZoneContext>().Options;
            var mockContext = new Mock<DeviceNZoneContext>(options);
            var mockDbSet = new Mock<DbSet<Device>>();
            mockContext.Setup(context => context.Set<Device>()).Returns(mockDbSet.Object);
            var repository = new TestDeviceRepository(mockContext.Object);
            Device expectedDevice = new Device { DeviceId = 1 };
            mockDbSet.Setup(DbSet => DbSet.Find(expectedDevice.DeviceId)).Returns(expectedDevice);

            //Act
            repository.Delete(expectedDevice.DeviceId);
            
            //Assert
            mockDbSet.Verify(DbSet => DbSet.Find(expectedDevice.DeviceId),Times.Once);
            mockDbSet.Verify(DbSet => DbSet.Remove(expectedDevice),Times.Once);
        }
    }
}