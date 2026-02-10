#include <stdlib.h>
#include <stdio.h>

int main() {
    int n[5];
    float s[5], t[5], novo_salario;
    for (int cont1 = 0; cont1 < 5; cont1++) {
        printf("Digite o numero do funcionario %d:\n", cont1 + 1);
        scanf("%d", &n[cont1]);
        printf("\nDigite o salario do funcionario %d:\n", cont1 + 1);
        scanf("%f", &s[cont1]);
        printf("\nDigite o tempo de servico, em anos, do funcionario %d:\n", cont1 + 1);
        scanf("%f", &t[cont1]);
        printf("\n");
    }
    for (int cont1 = 0; cont1 < 5; cont1++) {
        if (t[cont1] <= 5 && s[cont1] >= 800) printf("O funcionario %d nao tera direito a aumento!\n", n[cont1]);
        else {
            if (s[cont1] < 800) novo_salario = s[cont1] * 0.10 + s[cont1];
            else if (t[cont1] > 5) novo_salario = s[cont1] * 0.15 + s[cont1];
            else if (t[cont1] > 5 && s[cont1] < 800) novo_salario = s[cont1] * 0.35 + s[cont1];
            printf("O novo salario do funcionario %d sera de %.2f reais!\n", n[cont1], novo_salario);
        }
    }
}