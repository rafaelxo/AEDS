#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int angulo, voltas;
    printf("Insira o valor do angulo:\n");
    scanf("%d", &angulo);
    if (angulo > 360 || angulo < -360) {
        voltas = (int) angulo/360;
        angulo = angulo % 360;
    }
    if (angulo == 0 || angulo == 90 || angulo == 180 || angulo == 270 || angulo == 360 ||
        angulo == -90 || angulo == -180 || angulo == -270 || angulo == -360) {
            printf("\nO angulo esta em cima de um eixo!\n");
        }
    if ((angulo > 0 && angulo < 90) || (angulo < -270 && angulo > -360)) {
        printf("\n1o Quadrante!\n");
    } else if ((angulo > 90 && angulo < 180) || (angulo < -180 && angulo > -270)) {
        printf("\n2o Quadrante!\n");
    } else if ((angulo > 180 && angulo < 270) || (angulo < -90 && angulo > - 180)) {
        printf("\n3o Quadrante!\n");
    } else if ((angulo > 270 && angulo < 360) || (angulo < 0 && angulo > -90)) {
        printf("\n4o Quadrante!\n");
    }
    if (voltas < 0) {
        printf("\n%d voltas no sentido horario!\n", -voltas);
    } else {
        printf("\n%d voltas no sentido anti-horario!\n", voltas);
    }
}
