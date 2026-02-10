#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int numero;
    float quadrado, cubo, r2, r3;
    printf("Digite um numero inteiro e positivo para realizar os calculos:\n");
    scanf("%d", &numero);
    quadrado = pow(numero, 2);
    cubo = pow(numero, 3);
    r2 = sqrt(numero);
    r3 = pow (numero, 1.0/3.0);
    printf("\nOs resultados do quadrado, cubo, raiz quadrada e raiz cubica do valor inserido sao:\n%1.f\n%1.f\n%f\n%f\n", quadrado, cubo, r2, r3);

}
