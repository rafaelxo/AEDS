#include <stdlib.h>
#include <stdio.h>

int main() {
    int A[10], r[10], v[10], repetidos, cont_r = 0;
    for (int cont1 = 0; cont1 < 10; cont1++) {
        printf("Digite o valor da posicao %d do vetor:\n", cont1 + 1);
        scanf("%d", &A[cont1]);
    }
    for (int cont1 = 0; cont1 < 10; cont1++) {
        r[cont1] = 0;
        v[cont1] = 0;
    }
    printf("\nElementos repetidos no vetor:\n");
    for (int cont1 = 0; cont1 < 10; cont1++) {
        repetidos = 1;
        for (int cont2 = 0; cont2 < 10; cont2++) {
            if (cont1 != cont2 && A[cont1] == A[cont2]) repetidos++;
        }
        if (repetidos > 1) {
            for (int cont = 0; cont <= cont_r; cont++) {
                if (A[cont1] == r[cont]) repetidos = 0;
            }
            if (repetidos > 0) {
                r[cont_r - 1] = A[cont1];
                v[cont_r - 1] = repetidos;
                cont_r++;
            }
        }
    }
    for (int cont1 = 0; cont1 < cont_r - 1; cont1++) printf("O numero %d repetiu %d vezes!\n", r[cont1], v[cont1]);
}