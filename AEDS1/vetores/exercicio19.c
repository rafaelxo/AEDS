#include <stdlib.h>
#include <stdio.h>

int main() {
    char a[20], b[20], aux;
    for (int cont1 = 0; cont1 < 20; cont1++) {
        printf("Digite o valor da posicao %d do vetor A:\n", cont1 + 1);
        scanf(" %c", &a[cont1]);
    }
    for (int cont1 = 0; cont1 < 20; cont1++) {
        printf("Digite o valor da posicao %d do vetor B:\n", cont1 + 1);
        scanf(" %c", &b[cont1]);
    }
    printf("Vetor A:\n");
    for (int cont1 = 0; cont1 < 20; cont1++) printf("%c ", a[cont1]);
    printf("\nVetor B:\n");
    for (int cont1 = 0; cont1 < 20; cont1++) printf("%c ", b[cont1]);
    for (int cont1 = 0; cont1 < 20; cont1++) {
        aux = a[cont1];
        a[cont1] = b[19 - cont1];
        b[19 - cont1] = aux;
    }
    printf("\nO vetor A depois da troca realizada e:\n");
    for (int cont1 = 0; cont1 < 20; cont1++) printf("%c ", a[cont1]);
    printf("\nO vetor B depois da troca realizada e:\n");
    for (int cont1 = 0; cont1 < 20; cont1++) printf("%c ", b[cont1]);
}