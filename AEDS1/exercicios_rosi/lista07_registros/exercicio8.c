#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct moto {
    float consumo;
    float capacidade;
} Mt;

int main () {
    srand(6);
    float distancia = rand()%101;
    Mt moto;
    scanf("%f%f", &moto.consumo, &moto.capacidade);
    float autonomia = moto.consumo * moto.capacidade;
    float tanques = distancia / autonomia;
    if (tanques <= 1) printf("A moto não precisa parar para abastecer\n");
    else {
        int vezes = ceil(tanques) - 1;
        printf("A moto precisa parar %d vezes para abastecer\n", vezes);
    }
}