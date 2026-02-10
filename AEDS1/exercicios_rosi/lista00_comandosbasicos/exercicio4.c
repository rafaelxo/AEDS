#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.14159

int main() {
    float raio, perimetro, area;
    printf("Insira o valor do raio do circulo:\n");
    scanf("%f", &raio);
    perimetro = 2 * pi * raio;
    area = pi * pow(raio,2);
    printf("\nO perimetro e a area do circulo equivalem, respectivamente, a:\n%.2f\n%.2f\n", perimetro, area);
}
