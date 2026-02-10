#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int idade;
    printf("Insira a idade para verificar a maioridade:\n");
    scanf("%d", &idade);
    if (idade >= 18) {
        printf("\nIndividuo de maior!\n");
    } else {
        printf("\nIndividuo de menor!\n");
    }
}
