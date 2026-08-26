#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float valor, rendimento, novo_valor;
    char investimento;
    scanf("%f %c", &valor, &investimento);
    if (investimento == 'P') {
        rendimento = valor * 0.03;
    } else if (investimento == 'F') {
        rendimento = valor * 0.04;
    }
    novo_valor = valor + rendimento;
    printf("%.2f", novo_valor);
}
