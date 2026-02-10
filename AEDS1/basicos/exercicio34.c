#include <stdio.h>
#include <stdlib.h>

int main() {
    float base_maior, base_menor, altura, area;
    printf("Insira, respectivamente, as medidas da base maior e a base menor do trapezio e, depois, sua altura:\n");
    scanf("%f%f%f", &base_maior, &base_menor, &altura);
    area = ((base_maior + base_menor) * altura)/2.0;
    printf("\nA area do trapezio e:\n%.2f\n", area);
}