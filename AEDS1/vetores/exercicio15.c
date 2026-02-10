#include <stdlib.h>
#include <stdio.h>

int main() {
    int dividendo[10], divisor[5];
    for (int cont1 = 0; cont1 < 10; cont1++) {
        printf("Digite o valor da posicao %d do vetor X:\n", cont1 + 1);
        scanf("%d", &dividendo[cont1]);
    }
    for (int cont1 = 0; cont1 < 5; cont1++) {
        printf("\nDigite o valor da posicao %d do vetor Y:\n", cont1 + 1);
        scanf("%d", &divisor[cont1]);
    }
    for (int cont1 = 0; cont1 < 10; cont1++) {
        printf("\nO valor %d do vetor X na posicao %d eh divisivel por:\n", dividendo[cont1], cont1 + 1);
        for (int cont2 = 0; cont2 < 5; cont2++) {
            if (dividendo[cont1] % divisor[cont2] == 0) printf("%d na posicao %d!\n", divisor[cont2], cont2 + 1);
            else printf("Nenhum valor do vetor Y e divisor do vetor X!\n");
        }
    }
}