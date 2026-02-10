#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int p_racao, r_gato1, r_gato2, restante, consumo, juntos;
    printf("Insira o peso, em gramas, do pacote de racao comprado e a quantidade fornecida para cada um dos gatos ao dia:\n");
    scanf("%d", &p_racao);
    printf("\nQuantos gramas de racao voce fornece a cada um de seus gatos por dia?\n");
    scanf("%d", &r_gato1);
    r_gato2 = r_gato1;
    juntos = r_gato1 + r_gato2;
    consumo = juntos*5;
    restante = p_racao - consumo;
    printf("\nSeus gatos comem o equivalente a %d gramas cada, e o que sobra de racao no pacote apos 5 dias equivale a %d gramas.\n", juntos, restante);
}
