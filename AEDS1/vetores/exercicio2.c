#include <stdlib.h>
#include <stdio.h>

int main () {
    int quantidade[10], mais = 0, maior = 0;
    float preco[10], total_geral = 0, salario_final = 545;
    for (int cont1 = 0; cont1 < 10; cont1++) {
        printf("Digite a quantidade vendida do produto %d e seu respectivo preco:\n", cont1 + 1);
        scanf("%d%f", &quantidade[cont1], &preco[cont1]);
        printf("\nO valor total do produto %d, com %d vendas a um preco de %.2f reais, e de:\n%.2f!\n\n", cont1 + 1, quantidade[cont1], preco[cont1], quantidade[cont1] * preco[cont1]);
        total_geral += quantidade[cont1] * preco[cont1];
        if (quantidade[cont1] > maior) {
            maior = quantidade[cont1];
            mais = cont1 + 1;
        }
    }
    printf("\nO faturamento total e de:\n%.2f reais!\n", total_geral);
    printf("\nO valor total de comissao do vendedor e de:\n%.2f reais!\n", total_geral * 0.05);
    salario_final += total_geral * 0.05;
    printf("\nO salario final do vendedor e de:\n%.2f reais!\n", salario_final);
    printf("\nO produto com mais vendas, %d no total, e o produto %d!\n", mais, maior);
}