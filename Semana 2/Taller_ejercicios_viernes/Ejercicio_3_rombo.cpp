#include<stdio.h>
#include<math.h>

int main()
{
    float D=8, d=6;
    float lado = sqrt(pow(D/2,2) + pow(d/2,2));

    printf("area: %.2f\n", D*d/2);
    printf("perimetro: %.2f\n", 4 * lado);
    printf("lado: %.2f\n", lado);
}