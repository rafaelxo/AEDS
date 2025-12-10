#include <stdio.h>
#include <stdlib.h>

void swap (int vet[], int i, int j) {
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

void quicksort (int vet[], int esq, int dir) {
    int i = esq, j = dir;
    int pivo = vet[(esq + dir) / 2];
    while (i <= j) {
        while (vet[i] < pivo) i++;
        while (vet[j] > pivo) j--;
        if (i <= j) {
            swap(vet, i, j);
            i++; j--;
        }
    }
    if (esq < j) quicksort(vet, esq, j);
    if (i < dir) quicksort(vet, i, dir);
}
