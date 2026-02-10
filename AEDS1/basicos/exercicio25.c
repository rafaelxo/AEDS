#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int custo, convite, quantidade;
    printf("Insira o preco do convite e o custo para o espetaculo:\n");
    scanf("%d%d", &convite, &custo);
    quantidade = custo/convite;
    printf("\nA quantidade de convites a serem vendidos para cobrirem o custo do espetaculo e de:\n%d\n", quantidade);
}
