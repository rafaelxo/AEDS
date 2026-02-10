#include <stdio.h>
#include <stdlib.h>

void maiorMenor (int n1, int n2, int n3, int n4, int n5) {
    int maior = n1, menor = n1;
    if (n2 > maior) maior = n2;
    if (n3 > maior) maior = n3;
    if (n4 > maior) maior = n4;
    if (n5 > maior) maior = n5;
    if (n2 < menor) menor = n2;
    if (n3 < menor) menor = n3;
    if (n4 < menor) menor = n4;
    if (n5 < menor) menor = n5;
    printf("\nO menor e o maior valor sao, respectivamente:\n%d e %d\n", menor, maior);
}

int main () {
    int N, n1, n2, n3, n4, n5;
    printf("Insira quantas sequencias quer calcular:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira a sequencia de 5 numeros:\n");
        scanf("%d%d%d%d%d", &n1, &n2, &n3, &n4, &n5);
        maiorMenor(n1, n2, n3, n4, n5);
    }
}