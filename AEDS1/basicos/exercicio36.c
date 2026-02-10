#include <stdio.h>
#include <stdlib.h>

int main() {
    float d_maior, d_menor, area;
    printf("Insira, respectivamente, a medida da diagonal maior e da diagonal menor do losango:\n");
    scanf("%f%f", &d_maior, &d_menor);
    area = (d_maior*d_menor)/2.0;
    printf("\nA area do losango e:\n%.2f\n", area);
}