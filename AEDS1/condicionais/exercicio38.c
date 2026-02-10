#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float preco_inicial, aumento, preco_final;
    printf("Insira o preco inicial do produto:\n");
    scanf("%f", &preco_inicial);
    if (preco_inicial <= 50) {
        aumento = preco_inicial * 0.05;
    } else if ( preco_inicial > 50 && preco_inicial <= 100) {
        aumento = preco_inicial * 0.1;
    } else {
        aumento = preco_inicial * 0.15;
    }
    preco_final = preco_inicial + aumento;
    printf("\nO preco final desse produto e de %.2f reais!\n", preco_final);
    if (preco_final <= 80) {
        printf("\nProduto barato!\n");
    } else if (preco_final > 80 && preco_final <= 120) {
        printf("\nProduto normal!\n");
    } else if (preco_final > 120 && preco_final <= 200) {
        printf("\nProduto caro!\n");
    } else {
        printf("\nProduto muito caro!\n");
    }
}
