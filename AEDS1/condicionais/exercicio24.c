#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float preco_i, v_adicional, imposto, preco_c, desconto, preco_f;
    char tipo, refrigeracao;
    printf("Insira o preco, o tipo (A, L ou V) e se esse produto precisa ou nao de refrigeracao (S ou N):\n");
    scanf("%f %c %c", &preco_i, &tipo, &refrigeracao);
    if (refrigeracao == 'N') {
        if (tipo == 'A') {
            if (preco_i < 15) {
                v_adicional = 2;
            } else {
                v_adicional = 5;
            }
        } else if (tipo == 'L') {
            if (preco_i < 10) {
                v_adicional = 1.5;
            } else {
                v_adicional = 2.5;
            }
        } else {
            if (preco_i < 30) {
                v_adicional = 3;
            } else {
                v_adicional = 2.5;
            }
        }
    } else if (tipo == 'S') {
        if (tipo == 'A') {
            v_adicional = 8;
        } else {
            v_adicional = 0;
        }
    }
    printf("\nO valor adicional e de %.2f reais!\n", v_adicional);
    if (preco_i < 25) {
        imposto = preco_i * 0.05;
    } else {
        imposto = preco_i * 0.08;
    }
    printf("\nO valor do imposto e de %.2f reais!\n", imposto);
    preco_c = preco_i + imposto;
    printf("\nO preco de custo equivale a %.2f reais!\n", preco_c);
    if (tipo == 'A' && refrigeracao == 'S') {
        desconto = preco_c * 0.03;
    } else {
        desconto = 0;
    }
    printf("\nO valor do desconto e de %.2f reais!\n", desconto);
    preco_f = preco_c + v_adicional - desconto;
    printf("\nO novo preco do produto e de %.2f reais!\n", preco_f);
    if (preco_f <= 50) {
        printf("\nProduto barato!\n");
    } else if (preco_f > 50 && preco_f < 100) {
        printf("\nProduto normal!\n");
    } else {
        printf("\nProduto caro!\n");
    }
}
