using Microsoft.Win32;
using OfficeOpenXml;
using System;
using System.Data;
using System.Data.OleDb;
using System.IO;
using System.Windows;
using System.Windows.Controls;

namespace Lab1.view
{
    public partial class ExcelView : UserControl
    {
        public ExcelView()
        {
            InitializeComponent();
            DataContext = new viewmodel.Calculator();
        }

        private void Load_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog path = new OpenFileDialog();
            path.Filter = "Excel Files Only | *.xlsx; *.xls";
            path.Title = "Choose the File";
            path.ShowDialog();
            string connectionString = @"Provider=Microsoft.ACE.OLEDB.12.0;Data Source='" + path.FileName + "';Extended Properties='Excel 12.0;HDR=YES;IMEX=1';";
            OleDbConnection Ole = new OleDbConnection(connectionString);

            Ole.Open();
            OleDbCommand cmd = new OleDbCommand();
            cmd.CommandText = "SELECT * FROM [Sheet1$]";
            cmd.Connection = Ole;
            OleDbDataReader rd;
            try
            {
                rd = cmd.ExecuteReader();
            }
            catch
            {
                return;
            }

            DataTable dataTable = new DataTable();
            dataTable.Load(rd);
            if (!dataTable.Columns.Contains("Витрати палива на перевезення на 100 км (грн#)"))
            {
                dataTable.Columns.Add("Витрати палива на перевезення на 100 км (грн#)", typeof(double));
            }
            
            foreach (DataRow row in dataTable.Rows)
            {
                double valueForNewColumn = 424.0407675   + (-2.665692711) * Convert.ToDouble(row[0]) + (-2.736968837) * Convert.ToDouble(row[1]) + (-1.227116904) * Convert.ToDouble(row[2]);
                row["Витрати палива на перевезення на 100 км (грн#)"] = valueForNewColumn;
            }

            DataGrid.ItemsSource = dataTable.DefaultView;
            Ole.Close();
        }

        private void CreateExcelFile()
        {
            ExcelPackage.LicenseContext = LicenseContext.NonCommercial;
            using (var package = new ExcelPackage())
            {
                var worksheet = package.Workbook.Worksheets.Add("Sheet1");

                for (int col = 0; col < DataGrid.Columns.Count; col++)
                {
                    worksheet.Cells[1, col + 1].Value = DataGrid.Columns[col].Header;
                }

                for (int row = 0; row < DataGrid.Items.Count; row++)
                {
                    for (int col = 0; col < DataGrid.Columns.Count; col++)
                    {
                        var cellInfo = new DataGridCellInfo(DataGrid.Items[row], DataGrid.Columns[col]);
                        var cellContent = cellInfo.Column.GetCellContent(cellInfo.Item) as TextBlock;

                        if (cellContent != null && double.TryParse(cellContent.Text.Replace(".", ","), out double doubleparse))
                        {
                            worksheet.Cells[row + 2, col + 1].Value = doubleparse;
                        }
                        else if (cellContent != null)
                        {
                            worksheet.Cells[row + 2, col + 1].Value = cellContent.Text;
                        }
                    }
                }

                var saveFileDialog = new SaveFileDialog
                {
                    Filter = "Excel Files|*.xlsx",
                    DefaultExt = "xlsx"
                };

                if (saveFileDialog.ShowDialog() == true)
                {
                    var file = new FileInfo(saveFileDialog.FileName);
                    package.SaveAs(file);
                }
            }
        }

            private void Save_Click(object sender, RoutedEventArgs e)
        {
            CreateExcelFile();
        }
    }
}
