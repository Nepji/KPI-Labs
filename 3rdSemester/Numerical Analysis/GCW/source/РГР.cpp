#include <iostream>
#include <math.h>>

float Function(float X)
{
    return 22.98*cos(X+5.98)-2*X;
}

int main() {
    float Range[2] = {7,8}, X;
    float A = Range[0], B = Range[1];

    while(true)
    {
        if(abs(A-B) <= 0.001)
            break;
        X = (A+B)/2;
        std::cout << X << std::endl;
        Function(A)*Function(X) > 0 ? A=X : B=X;
    
    }
}
