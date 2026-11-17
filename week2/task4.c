#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *a = malloc(100);      /* will be freed          */
    char *b = malloc(200);      /* NEVER freed: a leak    */
    if (a == NULL || b == NULL) { perror("malloc"); return 1; }
    strcpy(a, "hello");
    strcpy(b, "world");
    printf("%s %s\n", a, b);
    free(a);
    return 0;
}
