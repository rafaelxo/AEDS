#include <stdlib.h>
#include <stdio.h>

void calculaJuros (float *atual, float *ajustado, float juros, int meses) {
    *ajustado = *atual;
    for (int cont1 = 1; cont1 <= meses; cont1++) *ajustado *= (1 + juros/100);
}

int main () {
    float *sal_atual = (float*)malloc(sizeof(float));
    float *sal_ajustado = (float*)malloc(sizeof(float));
    float juros;
    int meses;
    scanf("%f%f%d", sal_atual, &juros, &meses);
    calculaJuros(sal_atual, sal_ajustado, juros, meses);
    printf("%.2f\n", *sal_ajustado);
    free(sal_atual); free(sal_ajustado);
}