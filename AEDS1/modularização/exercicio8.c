#include <stdio.h>
#include <stdlib.h>

int duracao (int h_inicio, int min_inicio, int h_termino, int min_termino) {
    int minutos_inicio, minutos_termino;
    minutos_inicio = h_inicio * 60 + min_inicio;
    minutos_termino = h_termino * 60 + min_termino;
    return minutos_termino - minutos_inicio;
}

int main () {
    int N, h_inicio, min_inicio, h_termino, min_termino;
    printf("Insira quantos jogos quer analisar:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira a hora e o minuto do inicio do jogo, assim como do termino:\n");
        scanf("%d%d%d%d", &h_inicio, &min_inicio, &h_termino, &min_termino);
        printf("\nA duracao desse jogo foi de %d minutos!\n", duracao(h_inicio, min_inicio, h_termino, min_termino));
    }
}
