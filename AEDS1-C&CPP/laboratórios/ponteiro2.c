#include <stdlib.h>
#include <stdio.h>

void troca (int *ptrX, int *ptrY) {
    int troca = *ptrX;
    *ptrX = *ptrY;
    *ptrY = troca;
    printf("\nValor de ptrX depois da troca e %d\n", *ptrX);
    printf("O endereco de ptrX depois da troca e %x referenciando a %x\n", &ptrX, ptrX);
    printf("\nValor de ptrY depois da troca e %d\n", *ptrY);
    printf("O endereco de ptrY depois da troca e %x referenciando a %x\n", &ptrY, ptrY);
}

int main () {
    int *ptrX = (int*)malloc(sizeof(int));
    int *ptrY = (int*)malloc(sizeof(int));
    printf("Insira dois valores para ptrX e ptrY:\n");
    scanf("%d%d", ptrX, ptrY);
    printf("\nValor de ptrX e %d\n", *ptrX);
    printf("O endereco de ptrX e %x referenciando a %x\n", &ptrX, ptrX);
    printf("\nValor de ptrY e %d\n", *ptrY);
    printf("O endereco de ptrY e %x referenciando a %x\n", &ptrY, ptrY);
    troca(ptrX, ptrY);

    free(ptrX); free(ptrY);
}
