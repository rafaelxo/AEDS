#include <stdio.h>
#include <stdlib.h>

void verificacao(int num) {
    if (num > 0) printf("\nNumero positivo!");
    else if (num == 0) printf("\nNumero nulo!");
    else printf("\nNumero negativo!");
}

int main() {
    int N, num;
    printf("Insira quantas vezes quer verificar:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira o valor para verificar:\n");
        scanf("%d", &num);
        (verificacao(num));
    }
}
