using System;
using DAL.Repositories.Impl;
using DAL.Repositories.Interfaces;

namespace DAL.UnitOfWork
{
    public interface IUnitOfWork : IDisposable
    {
        IDeviceZoneRepository DeviceZoneRepository { get; }
        IDeviceRepository DeviceRepository { get; }
        void Save();
    }
}