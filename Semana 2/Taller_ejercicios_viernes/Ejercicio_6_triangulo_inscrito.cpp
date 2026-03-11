#include<stdio.h>
#include<math.h>

int main()
{
    float a2 = 9, b3 = 12, c2 = 15, r = 6;
    float p2 = (a2 + b3 + c2) / 2;

    printf("Semiperimetro: %.2f\n", p2);
    printf("Area: %.2f\n\n", r * p2);
}