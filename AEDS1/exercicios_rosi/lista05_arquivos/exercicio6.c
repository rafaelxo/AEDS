#include <stdio.h>
#include <stdlib.h>

int main () {
    FILE *arquivo = fopen("arq6.txt", "w");
    int num, soma = 0;
    scanf("%d", &num);
    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            printf("%d\n", i);
            soma += i;
        }
    }
    fprintf(arquivo, "%d", soma);
    fclose(arquivo);
}