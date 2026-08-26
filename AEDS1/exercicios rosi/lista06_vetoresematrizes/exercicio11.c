#include <stdlib.h>
#include <stdio.h>

int main () {
    int N, soma = 0;
    scanf("%d", &N);
    int *vet = (int*)malloc(N*sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", (vet + i));
        soma += *(vet + i);
    }
    printf("%d\n", soma);
}