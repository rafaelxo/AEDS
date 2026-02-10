#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float n1, n2, soma, raiz, op;
    printf("Menu de opcoes:\n\n1. Somar dois numeros.\n2. Raiz quadrada de um numero.\n\nInsira a opcao desejada:\n");
    scanf("%f", &op);
    if (op == 1) {
        printf("\nInsira os dois valores que deseja somar:\n");
        scanf("%f%f", &n1, &n2);
        soma = n1 + n2;
        printf("\nA soma desses valores e de:\n%.2f\n", soma);
    } else if (op == 2) {
        printf("\nInsira um valor para calcular sua raiz quadrada:\n");
        scanf("%f", &n1);
        raiz = sqrt(n1);
        printf("\nA raiz quadrada desse valor e de:\n%.2f\n", raiz);
    } else if (op != 1 && op !=2) {
        printf("\nOpcao invalida, escolha entre 1 e 2!\n");
    }
}
