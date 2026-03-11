#include<stdio.h>
#include<math.h>

int main()
{
    float lado=6;

    printf("area: %.2f\n", lado*lado);
    printf("perimetro: %.2f\n", 4*lado);
    printf("diagonal: %.2f\n", lado * sqrt(2));

    return 0;
}