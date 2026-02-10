#include <stdio.h>
#include <stdlib.h>

int main() {
    int q_lucro1000 = 0, q_lucro200 = 0;
    float p_compra, p_venda, lucro, lucro_total = 0;
    char investimento;
    printf("Insira o tipo de investimento (F para finalizar):\n");
    scanf(" %c", &investimento);
    while (investimento != 'F') {
        printf("\nInsira o preco de compra e o preco de venda da acao:\n");
        scanf("%f%f", &p_compra, &p_venda);
        lucro = p_compra - p_venda;
        lucro_total += lucro;
        printf("\nO lucro dessa acao e de %.2f reais!\n", lucro);
        if (lucro > 1000) {
           q_lucro1000++;
        } else if (lucro < 200) {
            q_lucro200++;
        }
        printf("Insira o tipo de investimento (F para finalizar):\n");
        scanf(" %c", &investimento);
    }
    printf("\nA quantidade de acoes com lucro superior a 1000 reais e de %d!\n", q_lucro1000);
    printf("\nA quantidade de acoes com lucro inferior a 200 reais e de %d!\n", q_lucro200);
    printf("\nO lucro total da empresa e de %.2f reais!\n", lucro_total);
}