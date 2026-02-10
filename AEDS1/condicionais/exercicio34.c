#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float s_medio, credito;
    printf("Insira o saldo medio do cliente:\n");
    scanf("%f", &s_medio);
    if (s_medio <= 200) {
        credito = s_medio * 0.1;
    } else if (s_medio > 200 && s_medio <= 300) {
        credito = s_medio * 0.2;
    } else if (s_medio > 300 && s_medio <= 400) {
        credito = s_medio * 0.25;
    } else if (s_medio > 400) {
        credito = s_medio * 0.3;
    }
    printf("\nO credito recebido e de %.2f reais!\n", credito);
}
