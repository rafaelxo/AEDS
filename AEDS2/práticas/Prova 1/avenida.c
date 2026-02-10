#include <stdio.h>

int main () {
    int d;
    scanf("%d", &d);
    int i = 0;
    while (i <= 2000) {
        if (d <= i) {
            int meio = (i + (i - 400)) / 2;
            if (d == meio) printf("%d\n", i - meio);
            else if (d < meio) printf("%d\n", d - (i - 400));
            else printf("%d\n", i - d);
            break;
        }
        i += 400;
    }
    return 0;
}
