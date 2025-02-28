using System.ComponentModel;
using Lab1;

namespace Lab1.viewmodel
{
    class MainViewModel : ObservableObj
    {
        public RelayCommand Calculator { get; set; }
        public RelayCommand ExcelTable { get; set; }

        public Calculator calculatorVM { get; set; }
        public ExcelTable exceltableVM { get; set; }
        private object _currentView;

        public object CurrentView
        {
            get => _currentView;
            set
            {
                _currentView = value;
                OnPropertyChanged();
            }
        }
        public MainViewModel()
        {
            calculatorVM = new Calculator();
            exceltableVM = new ExcelTable();

            Calculator = new RelayCommand(o =>
            {
                CurrentView = calculatorVM;
            });

            ExcelTable = new RelayCommand(o =>
            {
                CurrentView = exceltableVM;
            });
        }
    }
}

