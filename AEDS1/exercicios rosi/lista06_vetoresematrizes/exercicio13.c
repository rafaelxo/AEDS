#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char *p = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (*p) {
        printf("%c ", *p);
        p++;
    }
}