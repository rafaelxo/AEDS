#include <stdlib.h>
#include <stdio.h>

void ordenaVetor (int *vetor, int N) {
    int aux;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            if (*(vetor + j) > *(vetor + j + 1)) {
                aux = *(vetor + j);
                *(vetor + j) = *(vetor + j + 1);
                *(vetor + j + 1) = aux;
            }
        }
    }
}

int main () {
    int N;
    scanf("%d", &N);
    int *vet = (int*)malloc(N*sizeof(int));
    for (int i = 0; i < N; i++) scanf("%d", (vet + i));
    ordenaVetor(vet, N);
    for (int i = 0; i < N; i++) printf("%d ", *(vet + i));
    free(vet);
}