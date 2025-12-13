#include <stdio.h>
#include <stdlib.h>

void swap (int vet[], int i, int j) {
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

void ordenar (int vet[], int esq, int dir) {
    int i = esq, j = dir;
    int pivo = vet[esq + (dir - esq) / 2];
    while (i <= j) {
        while (vet[i] < pivo) i++;
        while (vet[j] > pivo) j--;
        if (i <= j) {
            swap(vet, i, j);
            i++; j--;
        }
    }
    if (esq < j) ordenar(vet, esq, j);
    if (i < dir) ordenar(vet, i, dir);
}

void pesquisa (int x, int array[], int n) {
    if (array == NULL || n <= 0) {
        printf("Elemento %d não encontrado!\n", x);
        return;
    }
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (array[meio] == x) {
            printf("Elemento %d encontrado na posição %d!\n", x, meio);
            return;
        } else if (x < array[meio]) dir = meio - 1;
        else esq = meio + 1;
    }
    printf("Elemento %d não encontrado!\n", x);
}

int main () {
    int n; scanf("%d", &n);
    int array[n];
    for (int i = 0; i < n; i++) scanf("%d", &array[i]);
    if (n > 1) ordenar(array, 0, n - 1);
    int x; scanf("%d", &x);
    pesquisa(x, array, n);
    return 0;
}
