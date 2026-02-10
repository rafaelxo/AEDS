#include <stdlib.h>
#include <stdio.h>

int main() {
    int x[10], y[5], rp[10], ri[10], soma, cont_rp = 0, cont_ri = 0;
    for (int cont1 = 0; cont1 < 10; cont1++) {
        printf("Digite o valor da posicao %d do vetor X:\n", cont1 + 1);
        scanf("%d", &x[cont1]);
    }
    for (int cont1 = 0; cont1 < 5; cont1++) {
        printf("\nDigite o valor da posicao %d do vetor Y:\n", cont1 + 1);
        scanf("%d", &y[cont1]);
    }
    for (int cont1 = 0; cont1 < 10; cont1++) {
        soma = x[cont1];
        for (int cont2 = 0; cont2 < 5; cont2++) soma += y[cont2];
        if (soma % 2 == 0) {
            rp[cont_rp] = soma;
            cont_rp++;
        } else {
            ri[cont_ri] = soma;
            cont_ri++;
        }
    }
    printf("\nVetor resultante com numeros pares:\n");
    for (int cont1 = 0; cont1 < cont_rp; cont1++) printf("%d ", rp[cont1]);
    printf("\n\nVetor resultante com numeros impares:\n");
    for (int cont1 = 0; cont1 < cont_ri; cont1++) printf("%d ", ri[cont1]);
}