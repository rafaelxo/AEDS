#include <stdio.h>
#include <stdlib.h>

int main() {
    float s_minimo, v_kwt, vn_conta, vd_conta;
    int q_kwt;
    printf("Insira,respectivamente, o salario minimo e a quantidade de kilowatts consumidos na sua residencia:\n");
    scanf("%f%d", &s_minimo, &q_kwt);
    v_kwt = s_minimo / 7.0 / 100.0;
    vn_conta = v_kwt * q_kwt;
    vd_conta = vn_conta * 0.9;
    printf("\nO valor do killowatts e da sua conta sem e com desconto sao, respectivamente:\n%.2f\n%.2f\n%.2f\n", v_kwt, vn_conta, vd_conta);
}
