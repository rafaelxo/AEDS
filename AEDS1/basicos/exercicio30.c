#include <stdio.h>
#include <stdlib.h>

int main() {
    float p_inicial, p_final;
    printf("Informe o preco inicial do produto:\n");
    scanf("%f", &p_inicial);
    p_final = p_inicial * 1.10;
        printf("\nO preco final do produto e:\n%.2f\n", p_final);
        return 0;
    }
