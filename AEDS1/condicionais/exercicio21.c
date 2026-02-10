#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int cod_estado, cod_carga, peso_kg;
    float peso_ton, preco_c, imposto, valor_t;
    printf("Insira, respectivamente, o codigo do estado (1 a 5), o peso em toneladas da carga e seu codigo (10 a 40):\n");
    scanf("%d%f%d", &cod_estado, &peso_ton, &cod_carga);
    peso_kg = peso_ton * 1000;
    printf("\nO peso em quilogramas da carga e de %d kg!\n", peso_kg);
    if (cod_carga >=10 && cod_carga <= 20) {
        preco_c = peso_kg * 100;
    } else if (cod_carga >= 21 && cod_carga <= 30) {
        preco_c = peso_kg * 250;
    } else if (cod_carga >= 31 && cod_carga <= 40) {
        preco_c = peso_kg * 340;
    }
    printf("\nO preco da carga e de %.2f reais\n", preco_c);
    switch (cod_estado) {
        case 1: imposto = preco_c * 0.35; break;
        case 2: imposto = preco_c * 0.25; break;
        case 3: imposto = preco_c * 0.15; break;
        case 4: imposto = preco_c * 0.05; break;
        case 5: imposto = 0; break;
    default: printf("\nCodigo de estado invalido!\n");
    }
    printf("\nO valor do imposto e de %.2f reais!\n", imposto);
    valor_t = preco_c + imposto;
    printf("\nO valor total da carga e de %.2f reais!\n", valor_t);
}
