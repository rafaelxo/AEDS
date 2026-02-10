#include <stdlib.h>
#include <stdio.h>

int main () {
    int vet1[10], vet2[10], vet3[20], cont2 = 0;
    for (int cont1 = 0; cont1 < 10; cont1++) {
        printf("Digite o valor da posicao %d do vetor 1:\n", cont1 + 1);
        scanf("%d", &vet1[cont1]);
        vet3[cont2] = vet1[cont1];
        cont2++;
        printf("Digite o valor da posicao %d do vetor 2:\n", cont1 + 1);
        scanf("%d", &vet2[cont1]);
        vet3[cont2] = vet2[cont1];
        cont2++;
    }
    for (int cont1 = 0; cont1 < 20; cont1++) printf("\nO valor da posicao %d do vetor 3, agrupando os dois vetores, e:\n%d\n", cont1 + 1, vet3[cont1]);
}