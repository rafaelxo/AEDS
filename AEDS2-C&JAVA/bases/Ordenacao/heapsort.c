#include <stdio.h>
#include <stdlib.h>

void swap (int vet[], int i, int j) {
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

void construir (int vet[], int tam) {
    int i = tam - 1;
    while (i > 0 && vet[i] > vet[(i - 1) / 2]) {
        swap(vet, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void reconstruir (int vet[], int tam) {
    int i = 0;
    while (2 * i + 1 < tam) {
        int filho = 2 * i + 1;
        if (filho + 1 < tam && vet[filho] < vet[filho + 1]) filho++;
        if (vet[i] < vet[filho]) {
            swap(vet, i, filho);
            i = filho;
        } else i = tam;
    }
}

void heap (int vet[], int n) {
    for (int tam = 2; tam <= n; tam++) construir(vet, tam);
    int tam = n;
    while (tam > 1) {
        swap(vet, 0, tam - 1);
        tam--;
        reconstruir(vet, tam);
    }
}
