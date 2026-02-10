#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void geraArquivoDados (int *ptrM, int *ptrN) {
    FILE *arq = fopen("numeros.txt", "w");
    int valor;
    *ptrM = rand()%10 + 1; *ptrN = rand()%10 + 1;
    fprintf(arq, "%d %d\n", *ptrM, *ptrN);
    for (int i = 0; i < *ptrM; i++) {
        for (int j = 0; j < *ptrN; j++) {
            valor = rand()%1000;
            fprintf(arq, "%3d ", valor);
        }
        fprintf(arq, "\n");
    }
    fprintf(arq, "\n");
    fclose(arq);
}

void geraArquivoSaida (int *somas, int *pares, int M, int N) {
    FILE *saida = fopen("saida.txt", "w");
    for (int ln = 0; ln < M; ln++) fprintf(saida, "%4d ", *(somas + ln));
    fprintf(saida, "\n");
    for (int col = 0; col < N; col++) fprintf(saida, "%d ", *(pares + col));
    fprintf(saida, "\n");
    fclose(saida);
}

void preenche (int *matriz, int totalLn, int totalCol) {
    FILE *entrada = fopen("numeros.txt", "r");
    fscanf(entrada, "%d%d", &totalLn, &totalCol);
    for (int ln = 0; ln < totalLn; ln++) {
        for (int col = 0; col < totalCol; col++) fscanf(entrada, "%d", (matriz + ln*totalCol + col));
    }
    fclose(entrada);
}

void exibeMatriz (int *mat, int totalLn, int totalCol) {
    for (int i = 0; i < totalLn; i++) {
        for (int j = 0; j < totalCol; j++) printf("%3d ", *(mat + i*totalCol + j));
        printf("\n");
    }
    printf("\n");
}

void somaLinhas (int *matriz, int *somas, int totalLn, int totalCol) {
    for (int ln = 0; ln < totalLn; ln++) {
        *(somas + ln) = 0;
        for (int col = 0; col < totalCol; col++) *(somas + ln) += *(matriz + ln*totalCol + col);
    }
}

void exibeVetor (int *vet, int total) {
    for (int i = 0; i < total; i++) printf("%d ", *(vet + i));
    printf("\n");
}

void quantPares (int *matriz, int *quantidades, int totalLn, int totalCol) {
    for (int col = 0; col < totalCol; col++) {
        *(quantidades + col) = 0;
        for (int ln = 0; ln < totalLn; ln++) {
            if (*(matriz + ln*totalCol + col)%2 == 0) (*(quantidades + col))++;
        }
    }
}

int main () {
    srand((unsigned)time(NULL));
    int M, N;
    geraArquivoDados(&M, &N);
    int mat[M][N], linhas[M], pares[N];
    printf("Matriz %d x %d\n", M, N);
    preenche(mat, M, N);
    printf("Dados gravados:\n");
    exibeMatriz(mat, M, N);
    somaLinhas(mat, linhas, M, N);
    printf("Soma das linhas:\n");
    exibeVetor(linhas, M);
    quantPares(mat, pares, M, N);
    printf("\nQuantidade de pares por coluna, respectivamente:\n");
    exibeVetor(pares, N);
    geraArquivoSaida(linhas, pares, M, N);
}