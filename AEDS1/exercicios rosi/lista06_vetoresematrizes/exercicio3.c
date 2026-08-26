#include <stdlib.h>
#include <stdio.h>

void preenche (int *x, int *y) {
    for (int i = 0; i < 10; i++) scanf("%d", (x + i));
    for (int i = 0; i < 10; i++) scanf("%d", (y + i));
}

void intercala (int *x, int *y, int *z) {
    for (int i = 0; i < 10; i++) {
        *(z + i*2) = *(x + i);
        *(z + i*2 + 1) = *(y + i);
    }
}

void exibe (int *z) {
    for (int i = 0; i < 20; i++) printf("%d ", z[i]);
}

int main () {
    int *x = (int*)malloc(10*sizeof(int));
    int *y = (int*)malloc(10*sizeof(int));
    int *z = (int*)malloc(20*sizeof(int));
    preenche(x, y); intercala(x, y, z); exibe(z);
    free(x); free(y); free(z);
}