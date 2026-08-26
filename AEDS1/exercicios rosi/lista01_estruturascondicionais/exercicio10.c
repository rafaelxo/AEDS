#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int h_extras, h_faltas;
    float min, gratificacao;
    scanf("%d%d", &h_extras, &h_faltas);
    min = (h_extras - (h_faltas * 2/3.0)) * 60;
    if (min < 600) {
        gratificacao = 100;
    } else if (min >= 600 && min < 1200) {
        gratificacao = 200;
    } else if (min >= 1200 && min < 1800) {
        gratificacao = 300;
    } else if (min >= 1800 && min < 2400) {
        gratificacao = 400;
    } else {
        gratificacao = 500;
    }
    printf("%.2f", gratificacao);
}
