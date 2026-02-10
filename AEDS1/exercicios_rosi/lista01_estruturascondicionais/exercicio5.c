#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float salario, aumento = 0.3, novo_salario;
    scanf("%f", &salario);
    if (salario < 500) {
        novo_salario = (salario * aumento) + salario;
        printf("%.2f", novo_salario);
    } else {
        printf("Sem reajuste");
    }
}
