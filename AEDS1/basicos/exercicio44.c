#include <stdio.h>
#include <stdlib.h>

int main() {
    int lado, comprimento;
    float area, w_potencia;
    printf("Insira o lado e o comprimento do comodo:\n");
    scanf("%d%d", &lado, &comprimento);
    area = lado * comprimento;
    w_potencia = area * 18;
    printf("\nA area do comodo e de %.2f e a potencia necessaria para a iluminacao do comodo equivale a %.1f watts.", area, w_potencia);
}