#include<stdio.h>
#include<math.h>

int main()
{
    float base=8, altura=6;

    printf("area: %.2f\n", base * altura);
    printf("perimetro: %.2f\n", 2 * (base + altura));
    printf("diagonal: %.2f\n", sqrt(base*base + altura*altura));
}