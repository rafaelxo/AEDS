#include <stdlib.h>
#include <stdio.h>

typedef struct retangulo {
    float largura;
    float altura;
    float area;
} Rt;

void area(Rt *r) {
    r->area = r->largura * r->altura;
    printf("A área do retângulo é: %.2f\n", r->area);
}

int main () {
    int N; scanf("%d", &N);
    Rt *retangulos = (Rt*)malloc(N*sizeof(Rt));
    for (int i = 0; i < N; i++) {
        scanf("%f%f", &retangulos[i].largura, &retangulos[i].altura);
        area(&retangulos[i]);
    }
}