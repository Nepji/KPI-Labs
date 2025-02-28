using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Lab1.view
{
    /// <summary>
    /// Interaction logic for CalculatorView.xaml
    /// </summary>
    public partial class CalculatorView : UserControl
    {
        public CalculatorView()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(Value1.Text) || string.IsNullOrEmpty(Value2.Text) || string.IsNullOrEmpty(Value3.Text)) return;
            double tempres = 424.0407675 + double.Parse(Value1.Text.Replace(".", ",")) * (-2.665692711) + double.Parse(Value2.Text.Replace(".", ",")) * (-2.736968837) + double.Parse(Value3.Text.Replace(".", ",")) * (-1.227116904);
            Result.Text = System.Convert.ToString(tempres);
        }

    }
}
