#include <stdlib.h>
#include <stdio.h>

int main() {
    float hora_t, h, min, conversao;
    printf("Insira o horario atual em formato (hh.mm) para realizar o calculo:\n");
    scanf("%f", &hora_t);
    h = (int)hora_t;
    min = (hora_t - h) * 100;
    conversao = h * 60 + min;
    printf("\nSe passaram %.2f minutos desde o inicio do dia (00:00)!\n", conversao);
}
