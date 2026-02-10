#include <stdio.h>
#include <stdlib.h>

int main() {
    int n_entrada, n_saida;
    printf("Insira um numero no formato CDU (centena, dezena, unidade) para realizar a inversao:\n");
    scanf("%d", &n_entrada);
    n_saida = (n_entrada % 10) * 100 + ((n_entrada / 10) % 10) * 10 + (n_entrada / 100);
    printf("\nO numero inserido em sua forma invertida e:\n%d\n", n_saida);
}