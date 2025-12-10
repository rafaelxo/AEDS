#include <stdio.h>
#include <stdlib.h>

void insertion (int vet[], int n) {
    for (int i = 1; i < n; i++) {
        int aux = vet[i];
        int j = i - 1;
        while (j >= 0 && vet[j] > aux) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = aux;
    }
}
