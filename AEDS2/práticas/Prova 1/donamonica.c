#include <stdio.h>
#include <stdlib.h>

int main () {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    int d = a - (b + c);
    if (d > b && d > c) printf("%d", d);
    else if (d > b && d < c) printf("%d", c);
    else if (d > c && d < b) printf("%d", b);
    else if (b > c) printf("%d", b);
    else printf("%d", c);
}
