#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float base, altura, perimetro, area, diagonal;
    printf("Insira a medida da base e da altura do retangulo:\n");
    scanf("%f%f", &base, &altura);
    perimetro = 2 * (base + altura);
    area = base * altura;
    diagonal = sqrt(pow(base, 2) + pow(altura,2));
    printf("\nO perimetro, a area e a digonal do retangulo equivalem, respectivamente a:\n%.2f\n%.2f\n%.2f\n", perimetro, area, diagonal);
}
