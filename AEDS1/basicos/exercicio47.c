#include <stdio.h>
#include <stdlib.h>

int main() {
    int lados, diagonais;
    printf("Digite o numero de lados desse poligono:\n");
    scanf("%d", &lados);
    diagonais = lados * (lados - 3) / 2;
    printf("\nO numero de diagonais desse poligono e:\n%d\n", diagonais);
}