#include <stdio.h>
#include <stdbool.h>

int main () {
    int n;
    scanf("%d", &n);
    while (n != 0) {
        int mark[n], leti[n];
        int sMark = 0, sLeti = 0;
        bool lMark = false, lLeti = false;
        for (int i = 0; i < n; i++) {
            scanf ("%d", &mark[i]);
            sMark += mark[i];
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &leti[i]);
            sLeti += leti[i];
        }
        if (n >= 3) {
            for (int i = 0; i < n - 2; i++) {
                if (mark[i] == mark[i + 1] && mark[i + 1] == mark[i + 2]) lMark = true;
                if (leti[i] == leti[i + 1] && leti[i + 1] == leti[i + 2]) lLeti = true;
            }
        }
        if (lMark && !lLeti) sMark += 30;
        if (lLeti && !lMark) sLeti += 30;
        if (sMark > sLeti) printf("M\n");
        else if (sLeti > sMark) printf("L\n");
        else printf("T\n");
        scanf("%d", &n);
    }
    return 0;
}
