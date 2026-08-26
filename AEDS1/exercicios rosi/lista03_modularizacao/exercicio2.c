#include <stdlib.h>
#include <stdio.h>

void mediaSalario () {
    int filhos, q_pessoas = 0;
    float salario, media = 0;
    scanf("%f%d", &salario, &filhos);
    while (salario != -1) {
        media += salario;
        q_pessoas++;
        scanf("%f%d", &salario, &filhos);
    }
    printf("%.2f", media/(q_pessoas*1.0));
}

int main () {
    mediaSalario();
}