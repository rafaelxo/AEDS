#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, q_primo = 0;
    printf("Insira a quantidade de numeros que quer verificar:\n");
    scanf("%d", &N);
    if (N <= 1) {
        printf("\nO numero deve ser maior que 1!\n");
        return 0;
    }
    for (int cont1 = 1; cont1 <= N; cont1++) {
        int num, div = 0;
        printf("\nInsira um numero maior que 1:\n");
        scanf("%d", &num);
        for (int cont2 = 1; cont2 <= num; cont2++) {
            if (num%cont2 == 0) {
               div++;
            }
        }
        if (div == 2) {
            printf("\nO numero %d e primo!\n", num);
            q_primo++;
        } else {
            printf("\nO numero %d nao e primo!\n", num);
        }
    }
    printf("\nA quantidade de numeros primos digitados foi %d!\n", q_primo);
}