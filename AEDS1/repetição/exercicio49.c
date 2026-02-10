#include <stdio.h>
#include <stdlib.h>

int main() {
    int cont1 = 1, N, valor, menor_valor, maior_valor, cont = 1;
    printf("Insira o 1 valor inteiro maior que 0:\n");
    scanf("%d", &valor);
    if (valor <= 0) {
        printf("\nPrograma finalizado!\n");
        return 0;
    }
    menor_valor = valor;
    maior_valor = valor;
    while (cont) {
        printf("\nInsira o proximo valor (0 para finalizar):\n");
        scanf("%d", &valor);
        if (valor == 0) {
            cont = 0;
        } else if (valor < 0) {
            printf("\nValor negativo!\n");
        } else {
            if (valor < menor_valor) {
                menor_valor = valor;
            }
            if (valor > maior_valor) {
                maior_valor = valor;
            }
        }
    }
    printf("\nO maior e o menor valor inseridos sao, respectivamente:\n%d e %d\n", maior_valor, menor_valor);
}
