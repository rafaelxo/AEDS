#include <stdlib.h>
#include <stdio.h>

int main () {
    int M1[4][5], M2[5][2], MF[4][2], soma = 0, mult;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) scanf("%d", &M1[i][j]);
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) scanf("%d", &M2[i][j]);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            soma = 0;
            for (int k = 0; k < 5; k++) soma += M1[i][k] * M2[k][j];
            MF[i][j] = soma;
        }
    }
    printf("Matriz final:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) printf("%d ", MF[i][j]);
        printf("\n");
    }
}