#include <stdlib.h>
#include <stdio.h>

int main() {
    int x[15], P[5], I[5], p_livre_p = 0, p_livre_i = 0;
    for (int cont1 = 0; cont1 < 15; cont1++) {
        printf("Digite o valor para a posicao %d do vetor:\n", cont1 + 1);
        scanf("%d", &x[cont1]);
    }
    for (int cont1 = 0; cont1 < 15; cont1++) {
        if (x[cont1]%2 == 0) {
            P[p_livre_p] = x[cont1];
            p_livre_p++;
        } else {
            I[p_livre_i] = x[cont1];
            p_livre_i++;
        }
        if (p_livre_p == 5) {
            printf("\nVetor de numeros par cheio:\n");
            for (int cont2 = 0; cont2 < p_livre_p; cont2++) printf("%d ", P[cont2]);
            p_livre_p = 0;
        }
        if (p_livre_i == 5) {
            printf("\nVetor de numeros impar cheio:\n");
            for (int cont2 = 0; cont2 < p_livre_i; cont2++) printf("%d ", I[cont2]);
            p_livre_i = 0;
        }
    }
    if (p_livre_p > 0) {
        printf("\nVetor de numeros par restante:\n");
        for (int cont2 = 0; cont2 < p_livre_p; cont2++) printf("%d ", P[cont2]);
    }
    if (p_livre_i > 0) {
        printf("\nVetor de numeros impar restante:\n");
        for (int cont2 = 0; cont2 < p_livre_i; cont2++) printf("%d ", I[cont2]);
    }

}