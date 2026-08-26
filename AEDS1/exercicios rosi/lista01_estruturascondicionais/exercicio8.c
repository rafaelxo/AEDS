#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float altura, peso_ideal;
    char sexo;
    scanf("%f %c", &altura, &sexo);
    if (sexo == 'H') {
        peso_ideal = (72.7 * altura) - 58;
    } else if (sexo == 'M') {
        peso_ideal = (62.1 * altura) - 44.7;
    }
    printf("%.2f", peso_ideal);
}
