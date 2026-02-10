#include <stdio.h>
#include <stdlib.h>

int main() {
    int l_menor = 0, l_meio = 0, l_maior = 0;
    float p_compra , p_venda, lucro, lucro_total = 0, s_p_compra = 0, s_p_venda = 0;
    scanf("%f%f", &p_compra, &p_venda);
    while (p_compra > 0) {
        lucro = p_venda - p_compra;
        s_p_compra += p_compra;
        s_p_venda += p_venda;
        if ((lucro*100/p_compra) < 10) {
            l_menor++;
        } else if ((lucro*100/p_compra) <= 20) {
            l_meio++;
        } else if ((lucro*100/p_compra) > 20) {
            l_maior++;
        }
        lucro_total += lucro;
        scanf("%f%f", &p_compra, &p_venda);
    }
    printf("%d\n%d\n%d\n%.2f\n%.2f\n%.2f", l_menor, l_meio, l_maior, s_p_compra, s_p_venda, lucro_total);
}
