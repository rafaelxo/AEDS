#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void gerarDados () {
    FILE *arquivo = fopen("arqReceba.txt", "w");
    int N, lados;
    float *tam = (float*)malloc(sizeof(float));
    srand((unsigned)time(NULL));
    N = rand()%100 + 1;
    fprintf(arquivo, "%d\n", N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        lados = (rand()%2) + 3;
        *tam = (float)(rand() % 1000) / 100;
        fprintf(arquivo, "%d %.2f\n", lados, *tam);
    }
    free(tam);
    fclose(arquivo);
}

void editarDados (int fusuario, float ftam) {
    FILE *arquivo = fopen("arqReceba.txt", "r");
    FILE *arquivo2 = fopen("arqTemp.txt", "w");
    int N, lados;
    float tam;
    fscanf(arquivo, "%d", &N);
    fprintf(arquivo2, "%d\n", N);
    for (int cont1 = 1; cont1 <= fusuario; cont1++) {
        fscanf(arquivo, "%d%f", &lados, &tam);
        fprintf(arquivo2, "%d %.2f\n", lados, tam);    
    }
    fscanf(arquivo, "%d%f", &lados, &tam);
    fprintf(arquivo2, "%d %.2f\n", lados, ftam);
    for (int cont1 = fusuario + 1; cont1 <= N; cont1++) {
        fscanf(arquivo, "%d%f", &lados, &tam);
        fprintf(arquivo2, "%d %.2f\n", lados, tam);
    }
    fclose(arquivo); fclose(arquivo2);
    remove("arqReceba.txt"); rename("arqTemp.txt", "arqReceba.txt");
}

int main () {
    gerarDados();
    FILE *arquivo = fopen("arqReceba.txt", "r");
    FILE *arquivo2 = fopen("arqResultado.txt", "w");
    int N, lados;
    float *tam = (float *)malloc(sizeof(float));
    fscanf(arquivo, "%d", &N);
    printf("\n%d figuras\n", N);
    fprintf(arquivo2, "%d figuras\n", N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        fscanf(arquivo, "%d%f", &lados, tam);
        printf("\n%d lados e tamanho %.2f\n", lados, *tam);
        if (lados == 3) {
            printf("\nTriangulo\n");
            printf("Area: %.2f\nPerimetro: %.2f\n", pow(*tam, 2) * sqrt(3) / 4, *tam * 3);
            fprintf(arquivo2, "\nTriangulo\n");
            fprintf(arquivo2, "Area: %.2f\nPerimetro: %.2f\n", pow(*tam, 2) * sqrt(3) / 4, *tam * 3);
        } else if (lados == 4) {
            printf("\nQuadrado\n");
            printf("Area: %.2f\nPerimetro: %.2f\n", pow(*tam, 2), *tam * 4);
            fprintf(arquivo2, "\nQuadrado\n");
            fprintf(arquivo2, "Area: %.2f\nPerimetro: %.2f\n", pow(*tam, 2), *tam * 4);
        }
    }
    int fusuario;
    float ftam;
    printf("\nInsira a figura que deseja alterar e seu novo tamanho:\n");
    scanf("%d%f", &fusuario, &ftam);
    editarDados(fusuario, ftam);
    printf("\nTamanho da figura %d alterado para %.2f!\n\nNovo resultado:", fusuario, ftam);
    if (lados == 3) {
        printf("\nTriangulo\n");
        printf("Area: %.2f\nPerimetro: %.2f\n", pow(ftam, 2) * sqrt(3) / 4, ftam * 3);
    } else if (lados == 4) {
        printf("\nQuadrado\n");
        printf("Area: %.2f\nPerimetro: %.2f\n", pow(ftam, 2), ftam * 4);
    }
    free(tam);
    fclose(arquivo); fclose(arquivo2);
}
