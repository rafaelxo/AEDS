#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int codigo;
    float preco;
    scanf("%f%d", &preco, &codigo);
    switch (codigo) {
        case 1: printf("Sul"); break;
        case 2: printf("Norte"); break;
        case 3: printf("Leste"); break;
        case 4: printf("Oeste"); break;
        case 5: case 6: printf("Nordeste"); break;
        case 7: case 8: case 9: printf("Sudeste"); break;
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20: printf("Sudoeste"); break;
        case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30: printf("Noroeste"); break;
    }
}
