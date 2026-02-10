#include <stdlib.h>
#include <stdio.h>

typedef struct ponto {
    int x, y;
} P;

int main () {
    int N; scanf("%d", &N);
    int horizontais, verticais;
    for (int i = 0; i < N; i++) {
        P pontos[3];
        horizontais = 0; verticais = 0;
        for (int i = 0; i < 3; i++) scanf("%d%d", &pontos[i].x, &pontos[i].y);
        if (pontos[0].x == pontos[1].x) verticais++;
        if (pontos[0].x == pontos[2].x) verticais++;
        if (pontos[1].x == pontos[2].x) verticais++;
        if (pontos[0].y == pontos[1].y) horizontais++;
        if (pontos[0].y == pontos[2].y) horizontais++;
        if (pontos[1].y == pontos[2].y) horizontais++;
        if (verticais == 0) printf("Nao ha alinhamentos verticais\n");
        else printf("alinhamentos verticais: %d\n", verticais);
        if (horizontais == 0) printf("Nao ha alinhamentos horizontais\n");
        else printf("alinhamentos horizontais: %d\n", horizontais);
    }
}