#include <stdio.h>

int main () {
    int n, h;
    while (scanf("%d%d", &n, &h) != EOF) {
        int quant = 0;
        for (int i = 0; i < n; i++) {
            int alt;
            scanf("%d", &alt);
            if (h >= alt) quant++;
        }
        printf("%d\n", quant);
    }
    return 0;
}
