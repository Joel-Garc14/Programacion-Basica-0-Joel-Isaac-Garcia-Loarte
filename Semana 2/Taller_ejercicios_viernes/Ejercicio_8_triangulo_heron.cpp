#include<stdio.h>
#include<cmath>

int main()
{
    float a3 = 3, b4 = 7, c3 = 5;
    float p3 = (a3 + b4 + c3) / 2;
    float areaHeron = sqrt(p3 * (p3 - a3) * (p3 - b4) * (p3 - c3));

    printf("Semiperimetro: %.2f\n", p3);
    printf("Area: %.2f\n", areaHeron);
}