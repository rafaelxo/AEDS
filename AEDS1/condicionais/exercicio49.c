#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int categoria;
    float preco, aumento, imposto, novo_preco;
    char refrigeracao;
    printf("Insira o preco do produto, sua categoria (1 a 3) e sua condicao (R ou N):\n");
    scanf("%f%d %c", &preco, &categoria, &refrigeracao);
    if (categoria < 1 || categoria > 3 || refrigeracao != 'R' && refrigeracao !='N') {
        printf("\nCategoria/refrigeracao invalidos!\n");
        return 0;
    }
    if (preco <= 25) {
        switch (categoria) {
            case 1: aumento = preco * 0.05; break;
            case 2: aumento = preco * 0.08; break;
            case 3: aumento = preco * 0.1; break;
        default: aumento = 0; break;
        }
    } else {
        switch (categoria) {
            case 1: aumento = preco * 0.12; break;
            case 2: aumento = preco * 0.15; break;
            case 3: aumento = preco * 0.18; break;
        default: aumento = 0; break;
        }
    }
    if (categoria == 2 || refrigeracao == 'R') {
        imposto = preco * 0.05;
    } else {
        imposto = preco * 0.08;
    }
    novo_preco = preco + aumento + imposto;
    printf("\nO valor do aumento, do imposto e o novo preco do produto equivalem, respectivamente, a:\n%.2f\n%.2f\n%.2f\n", aumento, imposto, novo_preco);
    if (novo_preco <= 50) {
        printf("\nProduto barato!\n");
    } else if (novo_preco > 50 && novo_preco <= 120) {
        printf("\nProduto normal!\n");
    } else {
        printf("\nProduto caro!\n");
    }
}
