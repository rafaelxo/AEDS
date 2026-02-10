#include <stdio.h>
#include <stdlib.h>

int main() {
    int voto, c1 = 0, c2 = 0, c3 = 0, c4 = 0, nulo = 0, branco = 0;
    scanf("%d", &voto);
    while (voto > 0) {
        switch (voto) {
            case 1: c1++; break;
            case 2: c2++; break;
            case 3: c3++; break;
            case 4: c4++; break;
            case 5: nulo++; break;
            case 6: branco++; break;
        }
        scanf("%d", &voto);
    }
    printf("%d\n%d\n%d\n%d\n%d\n%d", c1, c2, c3, c4, nulo, branco);
}
