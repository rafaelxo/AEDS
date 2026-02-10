#include <stdlib.h>
#include <stdio.h>

void conceito (float nota) {
    if (nota <= 39) {
        printf("F\n");
    } else if (nota <= 59) {
        printf("E\n");
    } else if (nota <= 69) {
        printf("D\n");
    } else if (nota <= 79) {
        printf("C\n");
    } else if (nota <= 89) {
        printf("B\n");
    } else {
        printf("A\n");
    }
}

int main () {
    int N;
    float nota;
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        scanf("%f", &nota);
        conceito(nota);
    }
}