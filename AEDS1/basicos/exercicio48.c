#include <stdio.h>
#include <stdlib.h>

int main() {
    int a1, a2, a3;
    printf("Insira o valor de dois angulos de um triangulo:\n");
    scanf("%d %d", &a1, &a2);
    a3 = 180 - a1 - a2;
    printf("\nO valor do terceiro angulo e de:\n%d\n", a3);
}
