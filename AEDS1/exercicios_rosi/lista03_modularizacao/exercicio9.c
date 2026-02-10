#include <stdlib.h>
#include <stdio.h>

float media (int N) {
    float nota, media = 0, q_aprovados = 0;
    for (int cont1 = 1; cont1 <= N; cont1++) {
        scanf("%f", &nota);
        if (nota >= 6) {
            q_aprovados++;
            media += nota;
        }
    }
    return (media/q_aprovados);
}

int main() {
    int N;
    scanf("%d", &N);
    printf("%.1f", media(N));
}