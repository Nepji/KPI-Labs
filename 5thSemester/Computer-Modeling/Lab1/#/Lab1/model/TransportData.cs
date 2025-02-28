using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class TransportData
    {
        public double TirePressure { get; set; } // Тиск в шинах, (атм.)
        public double FuelCost { get; set; }    // Вартість палива (грн.)
        public double CargoWeight { get; set; } // Вага вантажу, (т)
        public double FuelConsumptionPer100Km { get; set; } // Витрати палива на перевезення на 100 км (грн.)
    }
}
