#include <stdlib.h>
#include <stdio.h>

int main () {
    char lojas[8], produtos[4];
    float precos[4][8];
    for (int i = 0; i < 8; i++) {
        scanf(" %c", &lojas[i]);
    }
    for (int i = 0; i < 4; i++) {
        scanf(" %c", &produtos[i]);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) scanf("%f", &precos[i][j]);
    }
    printf("\nProdutos inferiores a 120 reais:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            if (precos[i][j] < 120) printf("Inicial do produto: %c\nInicial da loja: %c\nPreco: R$%.2f\n", produtos[i], lojas[i], precos[i][j]);
        }
    }
}