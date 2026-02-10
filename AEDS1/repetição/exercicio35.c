#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, num, soma_par = 0, soma_impar = 0;
    printf("Insira quantos numeros quer calcular:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira os valores:\n");
        scanf("%d", &num);
        if (num%2 == 0) {
            soma_par += num;
        } else if (num%2 > 0) {
            soma_impar += num;
        }
    }
    printf("\nA soma dos numeros pares e de %d!\n", soma_par);
    printf("\nA soma dos numeros impares e de %d!\n", soma_impar);
}
