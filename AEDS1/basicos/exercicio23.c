#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float n, f;
    int i, a;
    printf("Insira um numero real:\n");
    scanf("%f", &n);
    i = (int) n;
    f = n - i;
    a = (int) round(n);
    printf("\nO inteiro desse numero, sua parte fracionada e seu arredondamento sao, respectivamente:\n%d\n%f\n%d\n", i, f, a);
}
