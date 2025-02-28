using System;
using DAL.Entities;
using DAL.Repositories.Impl;
using DAL.Repositories.Interfaces;
using DAL.UnitOfWork;
using Microsoft.EntityFrameworkCore;

namespace DAL.EF
{
    public class EFUnitOfWork
        : IUnitOfWork
    {
        private DeviceNZoneContext db;
        private DeviceRepository _deviceRepository;
        private DeviceZoneRepository _deviceZoneRepository;

        public EFUnitOfWork(DbContextOptions options)
        {
            db = new DeviceNZoneContext(options);
        }
        public IRepository<Device> Devices
        {
            get
            {
                if (_deviceRepository == null)
                    _deviceRepository = new DeviceRepository(db);
                return _deviceRepository;
            }
        }
        public IRepository<DeviceZone> DeviceZones
        {
            get
            {
                if (_deviceZoneRepository == null)
                    _deviceZoneRepository = new DeviceZoneRepository(db);
                return _deviceZoneRepository;
            }
        }

        public IDeviceZoneRepository DeviceZoneRepository => _unitOfWorkImplementation1.DeviceZoneRepository;
        public IDeviceRepository DeviceRepository => _unitOfWorkImplementation1.DeviceRepository;

        public void Save()
        {
            db.SaveChanges();
        }
        private bool disposed = false;
        private IUnitOfWork _unitOfWorkImplementation;
        private IUnitOfWork _unitOfWorkImplementation1;

        public virtual void Dispose(bool disposing)
        {
            if (!this.disposed)
            {
                if (disposing)
                {
                    db.Dispose();
                }
                this.disposed = true;
            }
        }
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        
    }
}