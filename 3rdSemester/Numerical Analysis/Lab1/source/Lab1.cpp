#include <iostream>
#include <mutex>
using namespace std;

#define Array_rows 4
#define Array_col 5

#define b 5.98
#define A -4.02
#define B -15.02
#define k -5 

static int step = 1;


void Sort(double (&Array)[Array_rows][Array_col], int (&Xcounter)[Array_rows]);
void MatrixTriangleLower(double (&Array)[Array_rows][Array_col]);
void MatrixTriangleUpper(double (&Array)[Array_rows][Array_col]);
void XReturn(double (&Array)[Array_rows][Array_col], int (&Xcounter)[Array_rows]);
void PrintMatrix(double (&Array)[Array_rows][Array_col]);
void ViewBetween(double (&Array)[Array_rows][Array_col], int row, int mainrow,  double multiplie);
void ViewBetween(double (&Array)[Array_rows][Array_col], int row, int col1, int col2);
void ViewBetween(double (&Array)[Array_rows][Array_col], int row, double multiplie);



void main() {    
    int Xcounter[Array_rows];
    double Array[Array_rows][Array_col] =
            {
                    {k,b,1,-4,A+0.02},
                    {k-3,b+1,-2,9,1.2},
                    {k+1,-(b-0.52),-3,-1,2.01+B},
                    {k-1,-(b+1.58),-3.38,-1,A+B},
            };

    /////////////////////
    cout << "The initial view of the matrix:" << endl;
    PrintMatrix(Array);
    /////////////////////
    cout << "Sort the matrix: " << endl;
    //Sort(Array, Xcounter);
    /////////////////////
    cout << "Main operations on matrix: " << endl;
    MatrixTriangleLower(Array);
    MatrixTriangleUpper(Array);
    /////////////////////
    cout << "Return X to original form:" <<endl; 
    //XReturn(Array,Xcounter);
    /////////////////////
    cout << "The final view of the matrix: " << endl;
    PrintMatrix(Array);
    /////////////////////

    
}





void Sort(double (&Array)[Array_rows][Array_col], int (&Xcounter)[Array_rows])
{
    for(int i=0;i<Array_rows;i++)
        Xcounter[i]=i;
    for(int i=0;i<Array_rows-1;i++)
    {
        int MaxPosition=i;
        int lockKey=0;
        
        double MaxPositionValue = Array[i][i];
        for(int j=i;j<Array_col-1;j++)
        {
            if(Array[i][j]>MaxPositionValue)
            {
                MaxPositionValue=Array[i][j];
                MaxPosition = j;
                lockKey = 1;
            }
        }
        if(lockKey!=1) continue;
        for(int j=0;j<Array_rows;j++)
        {
            double Temp = Array[j][i];
            Array[j][i]=Array[j][MaxPosition];
            Array[j][MaxPosition]=Temp;
        }
        int XTemp;
        XTemp = Xcounter[i];
        Xcounter[i] = Xcounter[MaxPosition];
        Xcounter[MaxPosition] = XTemp;

        ViewBetween(Array,i+1,i+1,MaxPosition+1);
    }
}

void MatrixTriangleLower(double (&Array)[Array_rows][Array_col])
{
    double Temp[Array_col];
    for (int i = 0; i < Array_col - 1; i++)
    {
        double divisor = Array[i][i];
        for(int j=i;j<Array_col;j++)
        {
            Array[i][j] /= divisor;
        }
        ViewBetween(Array,i+1,divisor);
        for (int j = i + 1; j < Array_rows; j++)
        {
            double multiplier = Array[j][i] / Array[i][i];
            for (int n = 0; n < Array_col; n++)
            {
                Temp[n] = Array[i][n] * multiplier;
                Array[j][n] -= Temp[n];
            }
            ViewBetween(Array,j+1,i+1,multiplier);
        }
    }
}

void MatrixTriangleUpper(double (&Array)[Array_rows][Array_col])
{
    double Temp[Array_col];
    for (int i = Array_rows - 1; i >= 0; i--)
    {
        for (int j = i - 1; j >= 0; j--) {
            double multiplier = Array[j][i] / Array[i][i];
            for (int n = 0; n < Array_col; n++)
            {
                Temp[n] = Array[i][n] * multiplier;
                Array[j][n] -= Temp[n];
            }
            ViewBetween(Array,j+1,i+1,multiplier);
        }
    }
}

void XReturn(double (&Array)[Array_rows][Array_col], int (&Xcounter)[Array_rows])
{
    for (int i = 0; i < Array_rows-1; i++)
    {
        for (int j = i+1; j < Array_rows; j++)   
            {
            if (Xcounter[i] > Xcounter[j])
                {
                int temp = Xcounter[i];      
                Xcounter[i] = Xcounter[j];
                Xcounter[j] = temp;

                double Bigtemp  = Array[i][Array_col-1];
                Array[i][Array_col-1] = Array[j][Array_col-1];
                Array[j][Array_col-1]= Bigtemp;

                ViewBetween(Array,i+1,i+1,j+1);
                }
            }
    }
}

void ViewBetween(double (&Array)[Array_rows][Array_col], int row, int mainrow,  double multiplie)
{
    cout << "Step: " << step++ << "\tRow: " << row << " -= row: " << mainrow <<" * " << multiplie << endl;
    PrintMatrix(Array);
}

void ViewBetween(double (&Array)[Array_rows][Array_col], int row, int col1, int col2)
{
    
    cout << "Step: " << step++ << "\tFor Row: " << row << " Swap colum " << col1 <<" & " <<col2<<endl;
    PrintMatrix(Array);
}

void ViewBetween(double (&Array)[Array_rows][Array_col], int row, double multiplie)
{
    cout << "Step: " << step++ << "\tRow: " << row << " / " << multiplie << endl;
    PrintMatrix(Array);
}

void PrintMatrix(double (&Array)[Array_rows][Array_col])
{
    for(int i=0;i<Array_rows;i++)
    {
        for (int j= 0;j<Array_col-1;j++)
           printf("%13.5f ", Array[i][j]);
        printf(" || %13.5f ", Array[i][Array_col-1]);
        cout << endl;
    }
    cout << "-------------------------------------------------------" <<endl;
}
