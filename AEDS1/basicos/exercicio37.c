#include <stdio.h>
#include <stdlib.h>

int main() {
    float s_minimo, s_funcionario, quantidade_salarios;
    printf("Digite o salario minimo e o salario do funcionario:\n");
    scanf("%f %f", &s_minimo, &s_funcionario);
    quantidade_salarios = s_funcionario / s_minimo;
    printf("\nO funcionario recebe %.2f salarios minimos\n", quantidade_salarios);
}