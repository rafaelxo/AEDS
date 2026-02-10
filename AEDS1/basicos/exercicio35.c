#include <stdio.h>
#include <stdlib.h>

int main() {
    float lado, area;
    printf("Digite a medida do lado do quadrado:\n");
    scanf("%f", &lado);
    area = lado * lado;
    printf("\nA area do quadrado e:\n%.2f\n", area);
}