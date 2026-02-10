#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t tempo_atual;
    struct tm *info_tempo;
    char mesExtenso[20];
    time(&tempo_atual);
    info_tempo = localtime(&tempo_atual);
    int dia = info_tempo->tm_mday;
    int mes = info_tempo->tm_mon + 1;
    int ano = info_tempo->tm_year + 1900;
    int hora = info_tempo->tm_hour;
    int minuto = info_tempo->tm_min;
    switch (mes) {
        case 1:  sprintf(mesExtenso, "Janeiro"); break;
        case 2:  sprintf(mesExtenso, "Fevereiro"); break;
        case 3:  sprintf(mesExtenso, "Março"); break;
        case 4:  sprintf(mesExtenso, "Abril"); break;
        case 5:  sprintf(mesExtenso, "Maio"); break;
        case 6:  sprintf(mesExtenso, "Junho"); break;
        case 7:  sprintf(mesExtenso, "Julho"); break;
        case 8:  sprintf(mesExtenso, "Agosto"); break;
        case 9:  sprintf(mesExtenso, "Setembro"); break;
        case 10: sprintf(mesExtenso, "Outubro"); break;
        case 11: sprintf(mesExtenso, "Novembro"); break;
        case 12: sprintf(mesExtenso, "Dezembro"); break;
        default: sprintf(mesExtenso, "Inválido"); break;
    }
    printf("Data: %02d/%02d/%04d\n", dia, mes, ano);
    printf("Mes: %s\n", mesExtenso);
    printf("Hora: %02d:%02d\n", hora, minuto);

    return 0;
}
