#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void gerarDados () {
    FILE *entrada = fopen("entrada.txt", "w");
    srand((unsigned)time(NULL));
    int X = rand()%10 + 1, Y = rand()%10 + 1;
    printf("Quantidade de linhas e de colunas da matriz:\n%dx%d\n", X, Y);
    fprintf(entrada, "%d %d\n", X, Y);
    int M[X][Y];
    for (int cont1 = 0; cont1 < X; cont1++) {
        for (int cont2 = 0; cont2 < Y; cont2++) {
            M[cont1][cont2] = rand()%1000;
            printf("\nValor do elemento da coluna %d na linha %d:\n%d", cont2 + 1, cont1 + 1, M[cont1][cont2]);
            fprintf(entrada, "%d ", M[cont1][cont2]);
        }
        fprintf(entrada, "\n");
    }
    fclose(entrada);
}

int main () {
    gerarDados();
    FILE *entrada = fopen("entrada.txt", "r");
    int X, Y;
    fscanf(entrada, "%d %d", &X, &Y);
    int M[X][Y], soma[X], pares[Y];
    for (int cont1 = 0; cont1 < X; cont1++) soma[cont1] = 0;
    for (int cont2 = 0; cont2 < Y; cont2++) pares[cont2] = 0;
    for (int cont1 = 0; cont1 < X; cont1++) {
        for (int cont2 = 0; cont2 < Y; cont2++) fscanf(entrada, "%d", &M[cont1][cont2]);
    }
    fclose(entrada);
    for (int cont1 = 0; cont1 < X; cont1++) {
        for (int cont2 = 0; cont2 < Y; cont2++) soma[cont1] += M[cont1][cont2];
    }
    printf("\n\nSoma dos elementos por linha:\n");
    for (int cont1 = 0; cont1 < X; cont1++) printf("Linha %d = %d\n", cont1 + 1, soma[cont1]);
    for (int cont1 = 0; cont1 < X; cont1++) {
        for (int cont2 = 0; cont2 < Y; cont2++) {
            if (M[cont1][cont2]%2 == 0) pares[cont2]++;
        }
    }
    printf("\nQuantidade de pares por coluna:\n");
    for (int cont2 = 0; cont2 < Y; cont2++) printf("Coluna %d = %d\n", cont2 + 1, pares[cont2]);
}