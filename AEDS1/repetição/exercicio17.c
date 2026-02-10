#include <stdio.h>
#include <stdlib.h>

int main() {
    float s_carlos, s_joao, meses = 0;
    printf("Insira o salario de Carlos:\n");
    scanf("%f", &s_carlos);
    s_joao = s_carlos / 3;
    while (s_joao < s_carlos) {
        s_carlos += s_carlos * 0.02;
        s_joao += s_joao * 0.05;
        meses++;
    }
    printf("O salario de Joao sera maior que o de Carlos em %.0f meses!\n", meses);
}