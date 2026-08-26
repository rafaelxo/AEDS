#include <stdio.h>
#include <stdlib.h>

int main() {
    float num, den, decimal;
    printf("Insira, respectivamente, os valores do numerador e do denominador de uma fracao:\n");
    scanf("%f%f", &num, &den);
    decimal = num / den;
    printf("\nA fracao em decimal equivale a:\n%.2f\n", decimal);
}
