#include <stdio.h>
#include <stdlib.h>

int main() {
    float d_reais, d_dolar, d_alemao, d_libras;
    printf("Digite o valor que voce possui em reais:\n");
    scanf("%f", &d_reais);
    d_dolar = d_reais / 1.80;
    d_alemao = d_reais / 2.0;
    d_libras = d_reais / 3.57;
    printf("\nO valor equivalente em dolares, marcos alemãoes e libras esterlinas sao, respectivamente:\n%.2f\n%.2f\n%.2f\n", d_dolar, d_alemao, d_libras);
}