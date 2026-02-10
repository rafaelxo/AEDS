#include <stdio.h>
#include <stdlib.h>

int main()
{
    int base, altura;
    float area;
    printf("Insira a base e a altura, respectivamente, do triangulo para se calcular a area:\n");
    scanf("%d%d", &base, &altura);
    area = base*altura/2.0;
    printf("\nA area desse triangulo e:\n%.3f", area);
}
