#include <stdlib.h>
#include <stdio.h>

int main() {
    int cod;
    float x[5];
    for (int cont1 = 0; cont1 < 5; cont1++) {
        printf("Digite o valor para a posicao %d do vetor X:\n", cont1 + 1);
        scanf("%f", &x[cont1]);
    }
    do {
        printf("\nAgora insira o codigo (0, 1 ou 2):\n");
        scanf("%d", &cod);
    } while (cod < 1 || cod > 2);
    if (cod == 0) printf("\nFim!\n");
    else if (cod == 1) for (int cont1 = 0; cont1 < 5; cont1++) printf("\nValor da posicao %d do vetor:\n%f\n", cont1 + 1, x[cont1]);
    else if (cod == 2) for (int cont1 = 4; cont1 >= 0; cont1--) printf("\nValor da posicao %d do vetor:\n%f\n", cont1 + 1, x[cont1]);
}