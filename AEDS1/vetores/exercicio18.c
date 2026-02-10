#include <stdlib.h>
#include <stdio.h>

int main() {
    int x[20], contagem[6] = {0};
    for (int cont1 = 0; cont1 < 20; cont1++) {
        do {
            printf("Digite o valor %d sorteado pelo dado:\n", cont1 + 1);
            scanf("%d", &x[cont1]);
        } while (x[cont1] < 1 || x[cont1] > 6);
    }
    printf("\nOs valores sorteados foram:\n");
    for (int cont1 = 0; cont1 < 20; cont1++) printf("\nO valor do numero %d do vetor e:\n%d\n", cont1 + 1, x[cont1]);
    for (int cont1 = 0; cont1 < 20; cont1++) contagem[x[cont1] - 1]++;
    printf("\nContagem dos numeros sorteados:\n");
    for (int cont1 = 0; cont1 < 6; cont1++) printf("O numero %d foi sorteado %d vezes!\n", cont1 + 1, contagem[cont1]);
}