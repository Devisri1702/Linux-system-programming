#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("1. at the start         : break = %p\n", sbrk(0));

    char *a = malloc(100);
    printf("2. after malloc(100)    : break = %p\n", sbrk(0));

    char *b = malloc(100);
    printf("3. after 2nd malloc(100): break = %p\n", sbrk(0));

    free(a);
    free(b);
    printf("4. after free of both   : break = %p\n", sbrk(0));
    return 0;
}
