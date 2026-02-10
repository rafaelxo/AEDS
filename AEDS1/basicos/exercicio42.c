#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int raio;
    float comprimento, area, volume;
    printf("Digite o raio da esfera:\n");
    scanf("%d", &raio);
    comprimento = 2 * 3.1415 * raio;
    area = 4 * 3.1415 * pow(raio, 2);
    volume = (4 * 3.1415 * pow(raio, 3)) / 3.0;
    printf("\nO comprimento, a area e o volume da esfera sao, respectivamente:\n%.2f\n%.2f\n%.2f\n", comprimento, area, volume);
}