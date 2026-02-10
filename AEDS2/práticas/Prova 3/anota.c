#include <stdio.h>
#include <stdlib.h>

void swap (int *vet, int i, int j) {
    int temp = vet[i];
    vet[i] = vet[j];
    vet[j] = temp;
}

void ordenacao (int *vet, int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            if (vet[j] < vet[menor]) menor = j;
        }
        swap(vet, i, menor);
    }
}

int main () {
    int n, k;
    while (scanf("%d %d", &n, &k) != EOF) {
        int vet[n];
        for (int i = 0; i < n; i++) scanf("%d", &vet[i]);
        ordenacao(vet, n);
        int soma = 0;
        for (int i = n - 1; i >= n - k; i--) soma += vet[i];
        printf("%d\n", soma);
    }
    return 0;
}
