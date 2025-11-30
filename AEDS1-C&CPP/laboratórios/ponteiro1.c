#include <stdio.h>
#include <stdlib.h>

int main() {
    int y = 10;
    int *ptrY = &y;
    int **ptrPtrY = &ptrY;
    printf("O conteudo de y e %d\n", y);
    printf("O endereco de y e %x\n", &y);
    printf("O conteudo de ptrY e %d\n", *ptrY);
    printf("O endereco de ptrY e %x referenciando a %x\n", &ptrY, ptrY);
    printf("O conteudo de ptrPtrY e %d\n", **ptrPtrY);
    printf("O endereco de ptrPtrY e %x referenciando a %x\n", &ptrPtrY, ptrPtrY);
    printf("\n");

    (*ptrY)++;
    printf("O conteudo de y e %d\n", y);
    printf("O endereco de y e %x\n", &y);
    printf("O conteudo de ptrY e %d\n", *ptrY);
    printf("O endereco de ptrY e %x referenciando a %x\n", &ptrY, ptrY);
    printf("O conteudo de ptrPtrY e %d\n", **ptrPtrY);
    printf("O endereco de ptrPtrY e %x referenciando a %x\n", &ptrPtrY, ptrPtrY);
    printf("\n");

    ptrY++;
    printf("O conteudo de y e %d\n", y);
    printf("O endereco de y e %x\n", &y);
    printf("O conteudo de ptrY e %d\n", *ptrY);
    printf("O endereco de ptrY e %x referenciando a %x\n", &ptrY, ptrY);
    printf("O conteudo de ptrPtrY e %d\n", **ptrPtrY);
    printf("O endereco de ptrPtrY e %x referenciando a %x\n", &ptrPtrY, ptrPtrY);
    printf("\n");

    **ptrPtrY += 5;
    printf("O conteudo de y e %d\n", y);
    printf("O endereco de y e %x\n", &y);
    printf("O conteudo de ptrY e %d\n", *ptrY);
    printf("O endereco de ptrY e %x referenciando a %x\n", &ptrY, ptrY);
    printf("O conteudo de ptrPtrY e %d\n", **ptrPtrY);
    printf("O endereco de ptrPtrY e %x referenciando a %x\n", &ptrPtrY, ptrPtrY);
    printf("\n");
}
