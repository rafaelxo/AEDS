#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int idade;
    float peso;
    printf("Insira seu peso e sua idade para realizar a analise:\n");
    scanf("%f%d", &peso, &idade);
    if (idade < 20) {
        if (peso <= 60) {
            printf("\n9o grupo de risco!\n");
        } else if (peso > 60 && peso <= 90) {
            printf("\n8o grupo de risco!\n");
        } else if (peso > 90) {
            printf("\n7o grupo de risco!\n");
        }
    }
    else if (idade >= 20 && idade <= 50) {
        if (peso <= 60) {
            printf("\n6o grupo de risco!\n");
        } else if (peso > 60 && peso <= 90) {
            printf("\n5o grupo de risco!\n");
        } else if (peso > 90) {
            printf("\n4o grupo de risco!\n");
        }
    }
    else if (idade > 50) {
        if (peso <= 60) {
            printf("\n3o grupo de risco!\n");
        } else if (peso > 60 && peso <= 90) {
            printf("\n2o grupo de risco!\n");
        } else if (peso > 90) {
            printf("\n1o grupo de risco!\n");
        }
    }
}
