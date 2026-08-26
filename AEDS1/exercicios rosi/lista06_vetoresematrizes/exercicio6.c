#include <stdlib.h>
#include <stdio.h>

int main () {
    int matriz[4][4], somaElem = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) scanf("%d", &matriz[i][j]);
    }
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < i; j++) somaElem += matriz[i][j];
    }
    printf("%d\n", somaElem);
    for (int i = 0; i < 4; i++) printf("%d ", matriz[i][i]);
}