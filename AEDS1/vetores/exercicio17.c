#include <stdlib.h>
#include <stdio.h>

int main() {
    int x[6], soma_par = 0, soma_impar = 0, q_par = 0, q_impar = 0;
    for (int cont1 = 0; cont1 < 6; cont1++) {
        printf("Digite o valor da posicao %d do vetor X:\n", cont1 + 1);
        scanf("%d", &x[cont1]);
    }
    for (int cont1 = 0; cont1 < 6; cont1++) {
        if (x[cont1] % 2 == 0) {
            soma_par += x[cont1];
            q_par++;
        } else {
            soma_impar += x[cont1];
            q_impar++;
        }
    }
    if (q_par > 0) {
        printf("\nOs numeros pares do vetor X sao:\n");
        for (int cont1 = 0; cont1 < 6; cont1++) {
            if (x[cont1] % 2 == 0) printf("O numero %d na posicao %d!\n", x[cont1], cont1 + 1);
        }
        printf("\nA soma dos numeros pares e:\n%d\n", soma_par);
        printf("A quantidade de numeros pares e:\n%d\n", q_par);
    } else printf("\nNenhum numero par foi encontrado!\n");
    if (q_impar > 0) {
        printf("\nOs numeros impares do vetor X sao:\n");
        for (int cont1 = 0; cont1 < 6; cont1++) {
            if (x[cont1] % 2 != 0) printf("O numero %d na posicao %d!\n", x[cont1], cont1 + 1);
        }
        printf("\nA soma dos numeros impares e:\n%d\n", soma_impar);
        printf("A quantidade de numeros impares e:\n%d\n", q_impar);
    } else printf("\nNenhum numero impar foi encontrado!\n");
}