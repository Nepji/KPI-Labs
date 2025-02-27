#include <iostream>
#include <vector>

#define ZalikValue 227
#define variant 7
#define k 5
#define a 2
#define Test_off


using namespace std;

//////////////////////////////
float   a0=1,
        a1=-4,
        a2=2,
        a3=1,
        a4=-3,
        a5=2;
float XRange[2] = {-2,1.66};
float point = 0.00001;
bool Complex = false;
//////////////////////////////

vector<float> TempArray;
vector<float> Array = { a5*(1+a), a4, a3, a2, a1, k*a0 };

void Polovinki();
void Hord();
void Nbuton();

double Function(float Temp);
double PFunction(float Temp);

int main()
{
        cout << "Method Polovinki:" << endl;
        Polovinki();
        cout << "---------------------" << endl;
        cout << "---------------------" << endl;
        cout << "Method Hordiv:" << endl;
        Hord();
        cout << "---------------------" << endl;
        cout << "---------------------" << endl;
        cout << "Method Nbutona:" << endl;
        Nbuton();
        
}

double Function(float Temp)
{
        double result=0;
        for(int i=Array.size()-1;i>=0;i--)
        {
                if(i==0)
                        result += Array[Array.size()-1-i];
                else
                        result += Array[Array.size()-1-i]*pow(Temp, i);
        }
        return result; 
}
double PFunction(float Temp)
{
        double result=0;
        for(int i=Array.size()-1;i>=0;i--)
        {
                if(i==0) continue;
                result += Array[Array.size()-1-i]*pow(Temp, i-1)*i;
        }
        return result; 
}

double PPFunction(float Temp)
{
        double result=0;
        for(int i=Array.size()-1;i>=0;i--)
        {
                if(i==0 || i==1) continue;
                result += Array[Array.size()-1-i]*pow(Temp, i-2)*i*(i-1);
        }
        return result; 
}

void Polovinki()
{
        int INTER = 0;
        float A=XRange[0], B=XRange[1], C=XRange[0];
        do
        {
                C=(A+B)/2; INTER++;
#ifndef Test
                cout << "Step : C=(A+B)/2\tC:" << C << endl; 
                cout << "Step : F("<< A <<")*F("<<B<<") "<< (Function(A)*Function(C)<0? "< 0\nB=C" : "> 0\nA=C") << endl;
                cout << "---------------------" << endl;
#endif
                INTER+=2;
                if(Function(A)*Function(C)<0)
                        B=C;
                else
                        A=C;
                INTER++;
        }
        while (Function(C)!=0 && (B-A) > point);
        cout << "F("<< C <<") : " << Function(C) << endl << "\tUsed Iteration: " << INTER << endl;
}


void Hord()
{
        int INTER = 0;
        double A=XRange[0], B=XRange[1], X;
        do
        {
                INTER++;
                X = -(Function(A) * (B - A) / (Function(B) - Function(A))) + A;
#ifndef Test
                cout << "Step : -(Function("<<A<<") * ("<<B<<" - "<<A<<") / (Function("<<B<<") - Function("<<A<<"))) + "<<A<<"" << endl;  
                cout << "Function("<<A<<")*Function("<<X<<")<0 : B=X" << endl;
                cout << "---------------------" << endl;
#endif
                INTER++;
                if(Function(A)*Function(X)<0)
                        B=X;
                
                if(B-A <= point)
                        break;

                
        }
        while (abs(Function(X))>point);
        cout << "F("<< X <<") : " << Function(X) << endl << "\tUsed Iteration: " << INTER << endl;
}

void Nbuton()
{
        int INTER = 0,i=0;
        double A=XRange[0], B=XRange[1], X=0;

        if(Function(A)*PPFunction(A)>0)
                X=A;
        else if(Function(B)*PPFunction(B)>0)
                X=B;
        
        do
        {
                INTER++;
#ifndef Test
                        cout << "Step : X = "<<X<<"-(Function("<<X<<")/Function`("<<X<<")" << endl;
                        cout << "---------------------" << endl;
#endif
                
                X = X-(Function(X)/PFunction(X));
                
        }
        while (abs(Function(X))>point);
        cout << "F("<< X <<") : " << Function(X) << endl << "\tUsed Iteration: " << INTER << endl;
}