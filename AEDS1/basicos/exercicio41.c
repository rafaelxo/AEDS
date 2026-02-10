#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float c1, c2, h;
    printf("Insira o valor dos catetos do triangulo:\n");
    scanf("%f%f", &c1, &c2);
    h = sqrt(pow(c1, 2) + pow(c2, 2));
    printf("\nO valor da hipotenusa desse traingulo e de: %.3f\n", h);
}