#include <stdio.h>
#include <stdlib.h>

void swap (int vet[], int i, int j) {
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

void selection (int vet[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            if (vet[j] < vet[menor]) menor = j;
        }
        swap(vet, i, menor);
    }
}
