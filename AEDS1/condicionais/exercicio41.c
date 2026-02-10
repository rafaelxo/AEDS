#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float preco_atual, desconto, preco_novo;
    printf("Insira o preco atual do produto:\n");
    scanf("%f", &preco_atual);
    if (preco_atual <= 30) {
        desconto = 0;
    } else if (preco_atual > 30 && preco_atual <= 100) {
        desconto = preco_atual * 0.1;
    } else {
        desconto = preco_atual * 0.15;
    }
    preco_novo = preco_atual - desconto;
    printf("\nO desconto foi de %.2f reais e o novo preco desse produto e de %.2f reais!\n", desconto, preco_novo);
}
