#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>

using namespace std;


///////////////////////
const int A = 5,
          K = 0,
          ArraySize=5;
float Array[ArraySize] = {-5+K,-3+K,-1+K,1+K,3+K};
float FArray[ArraySize];
///////////////////////
float Function(float X)
{
    return sin((2.5)*X)+cbrt(X*5);
}

void Lagranj();
void Spline();

int main()
{
    cout.setf(ios::fixed);
    cout.precision(6);
    cout << "\tData:" << endl << "X:    ";
    for(int i=0;i<ArraySize;i++)
        cout << setw(11) << Array[i];
    cout << endl << "F(X): ";
    for(int i=0;i<ArraySize;i++)
    {
        FArray[i] = Function(Array[i]);
        cout << setw(11) << FArray[i];
    }
    cout << endl;


    ///////////////////////
    Lagranj();
    Spline();
    ///////////////////////
    ///
    cout << "\tData:" << endl << "X:    ";
    for(int i=0;i<ArraySize;i++)
        cout << setw(11) << Array[i];
    cout << endl << "F(X): ";
    for(int i=0;i<ArraySize;i++)
    {
        FArray[i] = Function(Array[i]);
        cout << setw(11) << FArray[i];
    }
    cout << endl;
    return 0;
}
float LagranjFunction(float X)
{
    float Result = 0;
    for (int i = 0; i < ArraySize; i++)
    {
        float L = 1;
        for (int j = 0; j < ArraySize; j++)
        {
            if (i == j) continue;
            
            L *= (X - Array[j]);
            L /= (Array[i] - Array[j]);
        }
        L *= FArray[i];
        Result += L;
    }
    cout << "LF(" << X << ") : " << Result << endl;
    return Result;
}

void Lagranj()
{
    float temp=Array[0];
    int counter=0;
    cout << "-----------|Lagranj Method|------------" << endl;
    do
    {
        cout << "---------------------------------------" << endl << "   Step: " << ++counter << endl;
        cout << "F("<<temp<<"):" << Function(temp) << endl;
        cout << "Error: " << (abs(Function(temp)-LagranjFunction(temp))) << endl;
        cout << "---------------------------------------" << endl;
        temp+=0.5;
    }while (temp>=Array[0] && temp<=Array[ArraySize-1]);
}

/////////////////////////////////////////////////////


float* Sweep(float** A, float* y, int n)
{
 float* alpha = new float[n];
 float* beta = new float[n];
 float* x = new float[n];
 for (int i = 0; i < n; i++)
 {
     if (i == 0)
     {
         alpha[i] = (-1) * (A[i][i + 1] / A[i][i]);
         beta[i] = y[i] / A[i][i];
     }
     else
     {
         float div = (A[i][i - 1] * alpha[i - 1]) + A[i][i];
         alpha[i] = (-1) * (A[i][i + 1] / div);
         beta[i] = (y[i] - (A[i][i - 1] * beta[i - 1])) / div;
     }
 }
 for (int i = n - 1; i >= 0; i--)
     x[i] = (i == n - 1) ? beta[i] : alpha[i] * x[i + 1] + beta[i];
 
 return x;
}
/////////////////////////////////////////////////////
void SplineFunction(float temp)
{
    float* a = new float[ArraySize - 1];
    float* c = new float[ArraySize - 1];
    float* d = new float[ArraySize - 1];
    float* b = new float[ArraySize - 1];
    float* h = new float[ArraySize - 1];
    float* vec = new float[ArraySize];
    float** matrix = new float* [ArraySize - 1];
    for (int i = 0; i < ArraySize - 1; i++)
    matrix[i] = new float[ArraySize - 1];
    for (int i = 0; i < ArraySize - 1; i++)
    {
         a[i] = FArray[i];
         h[i] = Array[i + 1] - Array[i];
         vec[i] = 0;
         for (int j = 0; j < ArraySize; j++)
            matrix[i][j] = 0;
    }
    for (int i = 0; i < ArraySize- 1; i++)
    {

         matrix[i][i - 1] = h[i - 1];
         matrix[i][i] = 2 * (h[i - 1] + h[i]);
         matrix[i][i + 1] = h[i];
         vec[i] = 3 * (((FArray[i + 1] - FArray[i]) / h[i]) + ((FArray[i] - FArray[i - 1]) / h[i -1]));
    }
    c = Sweep(matrix, vec, ArraySize - 1);
    for (int i = 0; i < ArraySize - 1; i++)
    {
         if (i != ArraySize - 2)
         {
             d[i] = (c[i + 1] - c[i]) / (3 * h[i]);
             b[i] = ((FArray[i + 1] - FArray[i]) / h[i]) - ((h[i] * (c[i + 1] + 2 * c[i])) / 3);
         }
         else
         {
             d[i] = (-1) * (c[i] / (3 * h[i]));
             b[i] = ((FArray[i] - FArray[i - 1]) / h[i]) - ((2 * h[i] * c[i]) / 3);
         }
    }
    int k = 0;
    for (int i = 1; i < ArraySize; i++)
        if (temp == Array[i])
            k = i - 1;

    cout << "X : " << temp << endl << "\ta : " << a[k] << "\tb :" << b[k] << "\tc :" << c[k] << "\td :" << d[k] << endl;
    printf("Pn(%.1f) = %.4f + %.4f * (X - %.4f) + %.4f * (X - %.4f)^2 + %.4f * (X - %.4f)^3", temp, 
    a[k], b[k], Array[k], c[k], Array[k], d[k], Array[k]);
}
 
void Spline()
{
    cout << "---------------|Splines|---------------" << endl;
    for(int i=1;i<ArraySize;i++)
    {
        cout << "---------------------------------------" << endl << "   Step: " << i << endl;
        SplineFunction(Array[i]);
        cout << endl << "---------------------------------------" << endl;
    }
}