#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int angulo;
    float altura, escada, radianos;
    printf("Insira o valor do angulo formado pela escada e a altura da parede:\n");
    scanf("%d%f", &angulo, &altura);
    radianos = angulo*3,14/180;
    escada = altura/sin(radianos);
    printf("\nA medida da escada e de:\n%.2f\n", escada);
}
