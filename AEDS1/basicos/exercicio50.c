#include <stdio.h>
#include <stdlib.h>

int main() {
    int h, min, h_minutos, t_min, min_seg;
    printf("Insira a hora seguida dos minutos:\n");
    scanf("%d%d", &h, &min);
    h_minutos = h * 60;
    t_min = h_minutos + min;
    min_seg = t_min * 60;
    printf("\nA hora em minutos, o tempo em minutos e em segundos, respectivamente, equivalem a:\n%d\n%d\n%d\n", h_minutos, t_min, min_seg);
}