#include <stdlib.h>
#include <stdio.h>

int main() {
    int x[10];
    for (int cont1 = 0; cont1 < 10; cont1++) {
        printf("Digite o valor da posicao %d do ponteiro X:\n", cont1 + 1);
        scanf("%d", &x[cont1]);
    }
    printf("\nValores maiores que 50:\n\n");
    for (int cont1 = 0; cont1 < 10; cont1++) {
        if (x[cont1] > 50) printf("O valor %d na posicao %d!\n", x[cont1], cont1 + 1);
        else printf("Nenhum valor maior que 50 encontrado!\n");
    }
}