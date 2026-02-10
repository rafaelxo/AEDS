#include <stdlib.h>
#include <stdio.h>

void recebeNotas (float *notas) {
    for (int i = 0; i < 10; i++) scanf("%f", (notas + i));
}

void media (float *notas) {
    int q = 0;
    float media = 0;
    for (int i = 0; i < 10; i++) media += notas[i];
    media /= 10;
    for (int i = 0; i < 10; i++) if (notas[i] >= 6) q++;
    printf("Media: %.2f\n", media);
    printf("Alunos acima da media: %d\n", q);
}

int main () {
    float *notas = (float*)malloc(10*sizeof(float));
    recebeNotas(notas); media(notas);
    free(notas);
}