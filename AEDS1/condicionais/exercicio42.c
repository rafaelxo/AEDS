#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int senha;
    printf("Insira a senha para o acesso:\n");
    scanf("%d", &senha);
    if (senha == 4531) {
        printf("\nAcesso liberado!\n");
    } else {
        printf("\nAcesso negado!\n");
    }
}
