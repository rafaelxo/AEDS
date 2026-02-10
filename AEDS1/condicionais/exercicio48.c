#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int codigo, quantidade;
    float preco_u, preco_t, desconto, preco_f;
    printf("Insira o codigo do produto e quantidade comprada:\n");
    scanf("%d%d", &codigo, &quantidade);
    if (codigo >= 1 && codigo <= 10) {
        preco_u = 10;
    } else if (codigo >= 11 && codigo <= 20) {
        preco_u = 15;
    } else if (codigo >= 21 & codigo <= 30) {
        preco_u = 20;
    } else if (codigo >= 31 && codigo <= 40) {
        preco_u = 30;
    } else {
        printf("\nCodigo invalido!\n");
        return 0;
    }
    preco_t = preco_u * quantidade;
    printf("\nO valor total da compra e de %.2f reais!\n", preco_t);
    if (preco_t <= 250) {
        desconto = preco_t * 0.05;
    } else if (preco_t > 250 && preco_t <= 500) {
        desconto = preco_t * 0.1;
    } else {
        desconto = preco_t * 0.15;
    }
    preco_f = preco_t - desconto;
    printf("\nO valor do desconto e de %.2f reais e o preco final do produto e de %.2f reais!\n", desconto, preco_f);
}
