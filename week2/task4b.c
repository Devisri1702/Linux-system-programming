#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

/* the 8 bytes just before the address malloc returned: glibc's "size" field */
static unsigned long size_field(void *p) {
    return ((unsigned long *)p)[-1];
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);

    int req[4] = { 24, 100, 1000, 5000 };
    char *p[4];

    printf("request  address(user ptr)   size field  chunk  usable  top-chunk-left  break\n");
    for (int i = 0; i < 4; i++) {
        p[i] = malloc(req[i]);
        if (p[i] == NULL) { perror("malloc"); return 1; }

        unsigned long f     = size_field(p[i]);
        unsigned long chunk = f & ~7UL;                      /* clear the 3 flag bits */
        /* the chunk right after this one is the "top chunk" (the unused rest of the heap) */
        unsigned long top   = *(unsigned long *)(p[i] + chunk - 8) & ~7UL;

        printf("%6d   %p   0x%-8lx  %5lu  %6zu  %14lu  %p\n",
               req[i], (void *)p[i], f, chunk, malloc_usable_size(p[i]), top, sbrk(0));
    }

    printf("\nfree(p[1]) and malloc(100) again:\n");
    void *old = p[1];
    free(p[1]);
    char *q = malloc(100);
    printf("old address %p, new address %p  -> %s\n", old, (void *)q,
           q == old ? "the freed block was reused" : "a different block");
    return 0;
}
