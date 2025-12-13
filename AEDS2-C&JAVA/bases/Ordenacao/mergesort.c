#include <stdio.h>
#include <stdlib.h>

void intercalar (int vet[], int esq, int meio, int dir) {
    int nEsq = meio - esq + 1, nDir = dir - meio;
    int *vetEsq = (int*)malloc((nEsq + 1)*sizeof(int));
    int *vetDir = (int*)malloc((nDir + 1)*sizeof(int));
    vetEsq[nEsq] = vetDir[nDir] = 2147483647;
    for (int i = 0; i < nEsq; i++) vetEsq[i] = vet[esq + i];
    for (int j = 0; j < nDir; j++) vetDir[j] = vet[meio + 1 + j];
    for (int j = 0, k = 0, i = esq; i <= dir; i++) {
        if (vetEsq[j] <= vetDir[k]) vet[i] = vetEsq[j++];
        else vet[i] = vetDir[k++];
    }
}

void merge (int vet[], int esq, int dir) {
    if (esq < dir) {
        int meio = (esq + dir) / 2;
        merge(vet, esq, meio);
        merge(vet, meio + 1, dir);
        intercalar(vet, esq, meio, dir);
    }
}
