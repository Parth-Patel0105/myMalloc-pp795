#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

/*
The correctness test driver. The correctness test plan explaining the design of each case is in the README.
*/

int main(int argc, char **argv){
        printf("case 1: tests that malloc only reserves unallocated memory by attempting to allocate space once the whole memory has been allocated.\n");
        int *a = malloc(4088);
        int *b = malloc(sizeof(int));
        printf("%p\n", b);
        //end of test
        free(a);

        printf("\ncase 2: tests that malloc correctly allocates space when there is enough.\n");
        int *z = malloc(sizeof(int));
        *z = 5;
        printf("%d\n", *z);
        //end of test
        free(z);

        printf("\ncase 3: tests that free deallocates memory.\n");
        double *d = malloc(4088);
        double *e = malloc(8);
        free(d);
        double *f = malloc(8);
        *f = 3.3;
        printf("%f\n", *f);
        //end of test
        free(f);

        printf("\ncase 4: tests that malloc() and free() arrange so that adjacent free blocks are coalesced.\n");
        int *l = malloc(576);
        int *m = malloc(576);
        int *n = malloc(576);
        int *o = malloc(576);
        int *p = malloc(576);
        int *q = malloc(576);
        int *r = malloc(576);
        free(m);
        free(o);
        malloc(1744);
        free(n);
        int *s = malloc(1744);
        *s = 777;
        printf("%d\n", *s);
        //end of test
        free(l);
        free(p);
        free(q);
        free(r);
        free(s);

        printf("\ncase 5: tests that free() cannot be called with an address not obtained from malloc().\n");
        int x1;
        free(&x1);
        //end of test

        printf("\ncase 6: tests that free() cannot be called with an address not at the start of a chunk.\n");
        int *p1 = malloc(sizeof(int)*2);
        free(p1 + 1);
        //end of test
        free(p1);
            
        printf("\ncase 7: tests that free() cannot be called a second time on the same pointer.\n");
        int *p2 = malloc(sizeof(int)*100);
        int *q2 = p2;
        free(p2);
        free(q2);
        //end of test
}
