#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

float calculaJuros (float *sal_atual, float juros, int meses) {
    float ajustado = *sal_atual;
    for (int cont1 = 1; cont1 <= meses; cont1++) ajustado *= (1 + juros/100);
    return ajustado;
}

void gerarDados () {
    FILE *arquivo = fopen("arqSalvar.txt", "w");
    float sal_atual, juros;
    int N, meses;
    srand((unsigned)time(NULL));
    N = rand()%100;
    fprintf(arquivo, "%d\n", N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        sal_atual = fmod(rand(), 100000);
        fprintf(arquivo, "\n%.2f\n", sal_atual);
        juros = fmod(rand(), 5);
        fprintf(arquivo, "%.2f\n", juros);
        meses = rand()%24;
        fprintf(arquivo, "%d\n", meses);
    }
    fclose(arquivo);
}

int main () {
    gerarDados();
    FILE *arquivo = fopen("arqSalvar.txt", "r");
    FILE *arquivo2 = fopen("arqSalario.txt", "w");
    float *sal_atual = (float*)malloc(sizeof(float));
    float juros;
    int N, meses;
    fscanf(arquivo, "%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        fscanf(arquivo, "%f%f%d", sal_atual, &juros, &meses);
        printf("Salario novo: %.2f\n", calculaJuros(sal_atual, juros, meses));
        fprintf(arquivo2, "%.2f\n", calculaJuros(sal_atual, juros, meses));
    }
    free(sal_atual);
    fclose(arquivo); fclose(arquivo2);
}
