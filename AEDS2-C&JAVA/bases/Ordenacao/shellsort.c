#include <stdio.h>
#include <stdlib.h>

void insercao (int vet[], int n, int gap, int alt) {
    for (int i = (alt + gap); i < n; i += alt) {
        int aux = vet[i];
        int j = i - alt;
        while (j >= 0 && vet[j] > aux) {
            vet[j + alt] = vet[j];
            j -= alt;
        }
        vet[j + alt] = aux;
    }
}

void shellsort(int vet[], int n) {
    int alt = 1;

    do {
        alt = (alt * 3) + 1;
    } while (alt < n);
    do {
        alt /= 3;
        for(int gap = 0; gap < alt; gap++) insercao(vet, n, gap, alt);
    } while (alt != 1);
}
