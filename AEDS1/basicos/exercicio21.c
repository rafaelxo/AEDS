#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float a_quadro, a_escada, d_escada;
    printf("Insira a altura desejada para o quadro e altura da escada:\n");
    scanf("%f%f", &a_quadro, &a_escada);
    d_escada = pow(a_escada, 2) - pow(a_quadro, 2);
    d_escada = pow(d_escada, 1.0/2.0);
    printf("\nA distancia em que a escada deve ser posicionada e de:\n%.2f\n", d_escada);

}
