#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int c_produto, peso_g, c_pais;
    float peso_kg, preco_i, imposto, preco_f;
    printf("Insira o peso do produto em kg, seu codigo e do pais de origem:\n");
    scanf("%f%d%d", &peso_kg, &c_produto, &c_pais);
    if (c_produto < 1 || c_produto > 10 || c_pais < 1 || c_pais > 3) {
        printf("\nCodigo do produto/pais invalido!\n");
        return 0;
    }
    peso_g = peso_kg * 1000;
    printf("\nO peso convertido desse produto e de %d gramas!\n", peso_g);
    if (c_produto >= 1 && c_produto <= 4) {
        preco_i = 10 * peso_g;
    } else if (c_produto >= 5 && c_produto <= 7) {
        preco_i = 15 * peso_g;
    } else if (c_produto >= 8 && c_produto <= 10) {
        preco_i = 20 * peso_g;
    }
    if (c_pais == 1) {
        imposto = 0;
    } else if (c_pais == 2) {
        imposto = preco_i * 0.15;
    } else if (c_pais == 3) {
        imposto = preco_i * 0.25;
    }
    preco_f = preco_i + imposto;
    printf("\nO preco inicial, o valor do imposto e o preco final do produto equivalem, respectivamente, a:\n%.2f\n%.2f\n%.2f\n", preco_i, imposto, preco_f);
}
