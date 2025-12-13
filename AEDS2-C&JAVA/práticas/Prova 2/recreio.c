#include <stdio.h>
#include <stdlib.h>

void insercao (int vet[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int aux = vet[i];
        int j = i - 1;
        while (j >= 0 && vet[j] < aux) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = aux;
    }
}

int main () {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int aln;
        scanf("%d", &aln);
        int fila[aln], final[aln];
        for (int i = 0; i < aln; i++) {
            scanf("%d", &fila[i]);
            final[i] = fila[i];
        }
        insercao(final, aln);
        int diff = 0;
        for (int i = 0; i < aln; i++) {
            if (fila[i] == final[i]) diff++;
        }
        printf("%d\n", diff);
    }
}
