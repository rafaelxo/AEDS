#include <stdio.h>
#include <stdlib.h>

int main() {
    float peso, novo_peso1, novo_peso2;
    printf("Digite seu peso atual:\n");
    scanf("%f", &peso);
    novo_peso1 = peso * 1.15;
    novo_peso2 = peso - (peso* 0.20);
    printf("\nSeu novo peso se engordar 15%% sera de:\n%.2f\n\ne se emagrecer 20%% sera de:\n%.2f\n", novo_peso1, novo_peso2);
}