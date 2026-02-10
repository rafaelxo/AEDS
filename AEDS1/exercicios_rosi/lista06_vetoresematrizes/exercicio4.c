#include <stdlib.h>
#include <stdio.h>

int main () {
    int N;
    scanf("%d", &N);
    int *vetor = (int*)malloc(N*sizeof(int)); 
    int maior;
    for (int i = 0; i < N; i++) {
        scanf("%d", (vetor + i));
        if (i == 0) maior = *(vetor + i);
        else {
            if (*(vetor + i) > maior) maior = *(vetor + i);
        }
    }
    printf("%d\n", maior);
    free(vetor);
}