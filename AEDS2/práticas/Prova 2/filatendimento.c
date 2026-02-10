#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Paciente {
    int hora, min, crit;
} Paciente;

int main () {
    int n;
    while (scanf("%d", &n) != EOF) {
        Paciente pac[n];
        for (int i = 0; i < n; i++) scanf("%d %d %d", &pac[i].hora, &pac[i].min, &pac[i].crit);
        int cont = 0;
        Paciente saida = {0, 0, 0};
        for (int i = 0; i < n; i++) {
            if (saida.hora < pac[i].hora || (saida.hora == pac[i].hora && saida.min <= pac[i].min)) {
                saida.hora = pac[i].hora;
                saida.min = pac[i].min;
            } else {
                int espera = (saida.hora - pac[i].hora) * 60 + (saida.min - pac[i].min);
                if (espera > pac[i].crit) {
                    cont++;
                    continue;
                }
            }
            saida.min += 30;
            if (saida.min >= 60) {
                saida.hora++;
                saida.min -= 60;
            }
        }
        printf("%d\n", cont);
    }
    return 0;
}
