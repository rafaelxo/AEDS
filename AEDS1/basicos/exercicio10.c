#include <stdio.h>
#include <stdlib.h>

#define pi 3.1415

int main()
{
    int raio;
    float area;
    printf("Insira o valor do raio do circulo a se calcular a area:\n");
    scanf("%d", &raio);
    area = pi*raio*raio;
    printf("\nA area desse circulo e de:\n%f", area);
}
