#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int angulo;
    float d_parede, m_escada;
    printf("Insira o angulo formado pela escada com o chao e sua distancia da parede:\n");
    scanf("%d%f", &angulo, &d_parede);
    m_escada = d_parede / cos(angulo);
    printf("\nA distancia da escada para o e de:\n%.2f\n", m_escada);
}
