#include <stdio.h>
#include <stdlib.h>

int main() {
    float preco, novo_preco;
    int venda;
    printf("Insira o preco atual do produto e sua quantidade de vendas mensal:\n");
    scanf("%f%d", &preco, &venda);
    if (venda < 500 || preco < 30) {
        novo_preco = preco + 0.1 * preco;
    } else if (venda >= 500 && venda < 1200 || preco >= 30 && preco < 80) {
        novo_preco = preco + 0.15 * preco;
    } else if (venda >=1200 || preco >= 80) {
        novo_preco = preco - 0.2 * preco;
    }
    printf("\nO novo preco desse produto e de %.2f reais!\n", novo_preco);
}
