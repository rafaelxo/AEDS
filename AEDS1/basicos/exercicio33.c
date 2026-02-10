#include <stdio.h>
#include <stdlib.h>

int main() {
    float peso_kg;
    int peso_g;
    printf("Digite seu peso em kilogramas:\n");
    scanf("%f", &peso_kg);
    peso_g = peso_kg * 1000;
    printf("\nSeu peso em gramas e:\n%d\n", peso_g);
}