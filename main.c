#include <stdio.h>
#include <stdlib.h>
typedef struct _note {
    char name[3];
    int duration;
    char intensity[5];
} note;

note myNote;


int main() {
    /* myNote.duration = 120; */
    /* printf("my note has duration of %d ms.\n", myNote.duration); */

    int x = sizeof(int)*10;

    printf("%lu\n", x);
    int *pa = (int *) malloc(sizeof(int)*10);

    int i;
    /* for (i=0; i<sizeof(int)*10; i++) */
    /*     printf("%pt\n", &pa[i]); */


    free(pa);
}
