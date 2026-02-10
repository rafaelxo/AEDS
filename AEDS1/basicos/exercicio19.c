#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n_degraus;
    float a_degrau, a_total;
    printf("Insira a altura do degrau e a altura que voce deseja alcancar:\n");
    scanf("%f%f", &a_degrau, &a_total);
    n_degraus = a_total/a_degrau;
    printf("\nO numero de degraus dessa escada e de:\n%d", n_degraus);
}
