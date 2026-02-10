

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int codigo;
    float preco;
    printf("Insira o preco e o codigo do produto:\n");
    scanf("%f%d", &preco, &codigo);
    if (codigo == 1) {
        printf("\nProduto de procedencia sul!\n");
    } else if (codigo == 2) {
        printf("\nProduto de procedencia norte!\n");
    } else if (codigo == 3) {
        printf("\nProduto de procedencia leste!\n");
    } else if (codigo == 4) {
        printf("\nProduto de procedencia oeste!\n");
    } else if (codigo == 5 || codigo == 6) {
        printf("\nProduto de procedencia nordeste!\n");
    } else if (codigo == 7 || codigo == 8 || codigo == 9) {
        printf("\nProduto de procedencia sudeste!\n");
    } else if (codigo >= 10 && codigo <= 20) {
        printf("\nProduto de procedencia centro-oeste!\n");
    } else if (codigo >= 21 && codigo <= 30) {
        printf("\nProduto de procedencia noroeste!\n");
    } else {
        printf("\nCodigo invalido!\n");
    }
}
