#include <stdio.h>
#include <stdlib.h>

int main() {
    float s_inicial, c1, c2, s_final;
    printf("Digite seu salario inicial:\n");
    scanf("%f", &s_inicial);
    c1 = s_inicial * 0.02;
    c2 = c1;
    s_final = s_inicial - c1 - c2;
    printf("\nSeu salario final e de: %.2f\n", s_final);
}
