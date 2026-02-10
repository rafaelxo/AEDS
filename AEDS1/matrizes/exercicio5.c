#include <stdlib.h>
#include <stdio.h>

int main () {
    int l_menor, col;
    float M[4][7], menor, maior;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 7; j++) {
            scanf("%f", &M[i][j]);
            if (i == 0 && j == 0) {
                menor = M[i][j];
                l_menor = 0;
            } else if (M[i][j] < menor) {
                menor = M[i][j];
                l_menor = i;
            }
        }
    }
    maior = M[l_menor][0];
    col = 0;
    for (int j = 0; j < 7; j++) {
        if (M[l_menor][j] > maior) {
            maior = M[l_menor][j];
            col = j;
        }
    }
    printf("Maior elemento: %f\nColuna do maior elemento: %d\nLinha do menor elemento: %d\n", maior, col + 1, l_menor + 1);
}