#include <iomanip>
#include <iostream>


using namespace std;

#define k 0
#define A 0.25*k
#define B 0.35*k

#define COLUMN 6
#define ROW 5

#define TEST_off

void ShowArray(float Array[5][6], string Massage)
{
    cout.setf(ios::fixed);
    cout.precision(6);
    cout << "---------------------------------------------" << endl <<  Massage << endl;
    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<COLUMN;j++)
            cout << setw(11) << Array[i][j];
        cout << endl;
    }
    cout << "---------------------------------------------" << endl;
}

bool CheakIterationMethod(float Array[ROW][COLUMN], bool (&BadRowMark)[ROW]);
void UpperGauseFix(float (&Array)[ROW][COLUMN], bool (&BadRowMark)[ROW]);


void MatrixFixer(float (&Array)[ROW][COLUMN], bool (&BadRowMark)[ROW]);
void ZeidelSolve(float (&Array)[ROW][COLUMN],float (&XResultArray)[3][ROW]);

int main(int argc, char* argv[])
{
    bool BadRowMark[ROW];
    float XResultArray[3][ROW];
    float Array[ROW][COLUMN] =
        {
            {5.18+A,1.12,0.95,1.32,0.83,6.19+B},
            {1.12,4.28-A,2.12,0.57,0.91, 3.21},
            {0.95,2.12,6.13+A,1.29,1.57,4.28-B},
            {1.32,0.57,1.29,4.57-A,1.25,6.25},
            {0.83,0.91,1.57,1.25,5.21+A,4.95+B}
        };
        ShowArray(Array,"Basic Array: ");
        if(!CheakIterationMethod(Array, BadRowMark))
        {
            MatrixFixer(Array, BadRowMark);
        }
        ZeidelSolve(Array,XResultArray);
}

bool CheakIterationMethod(float Array[ROW][COLUMN], bool (&BadRowMark)[ROW])
{
    bool reCheck = true;
    float ChecValue;

    for(int i=0;i<ROW;i++)
    {
        float sum=0;
        for(int j=0;j<ROW;j++)
        {
            if(i==j)
                ChecValue = abs(Array[i][j]);
            else
                sum += abs(Array[i][j]);
        }
        if(ChecValue>sum)
        {
            BadRowMark[i]=false;
            if(reCheck)
                reCheck = true;
        }
        else
        {
            reCheck = false;
            BadRowMark[i]=true;
        }

/////////////////////////////////////////
#ifndef TEST
        cout << "\tDiagonal advantage - row(" << i+1 << "): " << (ChecValue>sum ? "Passed" : "Fail") << endl;
#endif
    }
#ifndef TEST
    cout << "---------------------------------------------" << endl;
#endif
/////////////////////////////////////////     
    cout << "Matrix with diagonal advantage: " << (reCheck ? "true" : "false") << endl;
    return (reCheck ? true : false);
}

void UpperGauseFix(float (& Array)[ROW][COLUMN], bool (& BadRowMark)[ROW])
{
    double Temp[COLUMN];
    for (int i = ROW - 1; i >= 0; i--)
    {
        for (int j = i - 1; j >= 0; j--) {
            if(!BadRowMark[j]) continue;
            double multiplier = Array[j][i] / Array[i][i];
            cout << "\tDeduction Row (" << i+1 << ")  with multiplier:  " << multiplier << endl;
            for (int n = 0; n < COLUMN; n++)
            {
                Temp[n] = Array[i][n] * multiplier;
                Array[j][n] -= Temp[n];
            }
        }
    }
    ShowArray(Array, "*Second option* Fixed Array:");
}


void MatrixFixer(float (&Array)[ROW][COLUMN], bool (&BadRowMark)[ROW])
{
    float temp[COLUMN];
    cout << "Fix Log:" << endl;
    for (int i = 0; i < COLUMN - 1; i++)
    {
        float divisor = Array[i][i];
        
        if(BadRowMark[i])
        {
            cout << "\tDivide diagonal in row ("<< i+1 <<") to \"one\"" << endl;
            for(int j=0;j<COLUMN;j++)
                Array[i][j] /= divisor;
        }

        if(i+1==ROW || !BadRowMark[i+1]) continue;
        float multiplier = Array[i+1][i] / Array[i][i];
        cout << "\tDeduction Row (" << i+2 << ")  with multiplier:  " << multiplier << endl;
        for (int n = 0; n < COLUMN; n++)
        {
            temp[n] = Array[i][n] * multiplier;
            Array[i+1][n] -= temp[n];
        }
    }
    ShowArray(Array, "Fixed Array:");


for(int i=0;i<ROW;i++)
{
    float del = Array[i][i]; 
    for(int j=0;j<COLUMN;j++)
        Array[i][j]/=del;
}
    ShowArray(Array, "Divide diagonals to \"one\"");
    if(!CheakIterationMethod(Array, BadRowMark))
        UpperGauseFix(Array,BadRowMark);
}

void ZeidelSolve(float (&Array)[ROW][COLUMN],float (&XResultArray)[3][ROW])
{
    cout << "---------------------------------------------" << endl;
    for(int i=0;i<3;i++)
        for(int j=0;j<ROW;j++)
            XResultArray[i][j]=0;
    
    float XSUM,p=1;
    do
    {
        XSUM=0;
        cout << "Approximation (" << (int)p++ << ") : "; 
        for(int i=0;i<ROW;i++)
        {
            float SUM=0;
            for(int j=0;j<ROW;j++)
            {
                if(i>j) SUM+=Array[i][j]*XResultArray[2][j];
                else if(i<j) SUM+=Array[i][j]*XResultArray[1][j];
            }
            XResultArray[2][i] = Array[i][COLUMN-1]-SUM;
            XResultArray[0][i] = abs(XResultArray[2][i]-XResultArray[1][i]);
            XResultArray[1][i]=XResultArray[2][i];
            cout << XResultArray[1][i] << " ";
            XSUM += XResultArray[0][i];
        }
        cout << endl;
    }while(XSUM >= 0.00001);
    
    cout << endl << "Rusult:" << endl;
    for(int i=0;i<ROW;i++)
        cout << "\tX(" << i+1 << ") : " << XResultArray[1][i] << endl;
    cout << endl << "Accuracy (delta X):" << endl;
    for(int i=0;i<ROW;i++)
        cout << "\tX(" << i+1 << ") : " <<  XResultArray[0][i] << endl;

    XSUM=0;
    for(int i=0;i<ROW;i++)
        XSUM+=pow(XResultArray[0][i],2);
    double AccuracyResult = sqrt(XSUM/ROW);
    cout << endl << "SQRT Accuracy (delta X):" << AccuracyResult << endl;
}   