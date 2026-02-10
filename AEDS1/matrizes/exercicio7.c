#include <stdlib.h>
#include <stdio.h>

int main () {
    int M[5][7], maior, menor, linha, coluna, cont = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) scanf("%d", &M[5][7]);
    }
    for (int i = 0; i < 5; i++) {
        menor = M[i][0];
        linha = i;
        coluna = 0;
        for (int j = 0; j < 7; j++) {
            if (M[i][j] < menor) {
                menor = M[i][j];
                linha = i;
                coluna = j;
            }
        }
        maior = M[0, coluna];
        for (int j = 0; j < 5; j++) {
            if (M[j][coluna] > maior) maior = M[j][coluna];
        }
        if (menor = maior) {
            printf("%d e o ponto de sela, na posicao %d linha e %d coluna!\n", maior, linha, coluna);
            cont++;
        }
    }
    if (cont == 0) printf("Ponto de sela inexistente!\n");
}