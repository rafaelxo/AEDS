#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int pes, polegadas;
    float jardas, milhas;
    printf("Insira a quantidade de pes para realizar os calculos:\n");
    scanf("%d", &pes);
    polegadas = pes*12;
    jardas = pes/3.0;
    milhas = jardas/1760.0;
    printf("\nOs respectivos valores da conversao de pes em polegadas, jardas e milhas sao:\n%d\n%f\n%f", polegadas, jardas, milhas);

}
