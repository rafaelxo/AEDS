#include <stdio.h>
#include <stdlib.h>

int main() {
    int hora_i, min_i, hora_t, min_t, hora_d, min_d;
    printf("Insira a hora e o minuto de entrada no jogo:\n");
    scanf("%d%d", &hora_i, &min_i);
    printf("\nInsira a hora e o minuto de saida do jogo:\n");
    scanf("%d%d", &hora_t, &min_t);
    if (min_i > min_t) {
        min_t = min_t + 60;
        hora_t = hora_t - 1;
    } if (hora_i > hora_t) {
        hora_t = hora_t + 24;
    }
    min_d = min_t - min_i;
    hora_d = hora_t - hora_i;
    printf("\nSua jogatina durou %d horas e %d minutos!\n", hora_d, min_d);
}
