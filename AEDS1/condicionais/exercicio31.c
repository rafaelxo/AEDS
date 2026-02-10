#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int opcao;
    float n1, n2, potencia, r2n1, r2n2, r3n1, r3n2;
    printf("Menu de opcoes:\n\n1. Potencia\n2. Raiz quadrada\n3. Raiz cubica\n\nEscolha a opcao desejada:\n");
    scanf("%d", &opcao);
    if (opcao < 1 || opcao > 3) {
        printf("\nOpcao invalida!\n");
        return 1;
    }
    printf("\nAgora, insira os dois valores para realizar o calculo desejado:\n");
    scanf("%f%f", &n1, &n2);
    if (opcao == 2) {
        if (n2 < 0) {
            printf("\nNenhum valor pode ser negativo!\n");
            return 0;
        }
    }
    potencia = pow(n1, n2);
    r2n1 = sqrt(n1);
    r2n2 = sqrt(n2);
    r3n1 = cbrt(n1);
    r3n2 = cbrt(n2);
    switch (opcao) {
        case 1: printf("\nA potencia dos valores equivale a:\n%.2f\n", potencia); break;
        case 2: printf("\nA raiz quadrada dos valores equivale a:\n%.2f e %.2f\n", r2n1, r2n2); break;
        case 3: printf("\nA raiz cubica dos valores equivale a:\n%.2f e %.2f\n", r3n1, r3n2); break;
    default: printf("\nOpcao invalida!\n");
    }
}
