#include <stdio.h>
#include <stdlib.h>

float acrescimo (float p_antigo, float p_atual) {
    return (p_atual - p_antigo)/p_antigo*100;
}

int main () {
    float p_antigo, p_atual;
    printf("Insira, respectivamente, o preco antigo e o preco atual do produto:\n");
    scanf("%f%f", &p_antigo, &p_atual);
    printf("\nO percentual de acrescimo do valor desse produto e de %.2f%%!\n", acrescimo(p_antigo, p_atual));
}