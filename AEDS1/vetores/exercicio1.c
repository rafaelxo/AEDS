#include <stdlib.h>
#include <stdio.h>

int main () {
    int x[10];
    for (int cont1 = 0; cont1 < 10; cont1++) {
        printf("Insira o valor da posicao %d do vetor:\n", cont1);
        scanf("%d", &x[cont1]);
    }
    for (int cont1 = 0; cont1 < 10; cont1++) {
        int divisores = 0;
        for (int cont2 = 1; cont2 <= x[cont1]; cont2++) if (x[cont1] % cont2 == 0) divisores++;
        if (divisores <= 2) printf("O numero %d (na posicao %d do vetor) e primo\n", x[cont1], cont1);
        else printf("O numero %d (na posicao %d do vetor) nao e primo\n", x[cont1], cont1);
    }
}
