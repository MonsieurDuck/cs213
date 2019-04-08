#include <stdlib.h>
#include <stdio.h>

int *a;

void sort (int n) {
    int t;
    for (int i=n-1; i>0; i--)
        for (int j=i-1; j>=0; j--)
            if (*(a+i) < *(a+j)) {
                t = *(a+i);
                *(a+i)= *(a+j);
                *(a+j) = t;
            }
}

int main (int argc, char** argv) {
    char* ep;
    int   n;
    n = argc - 1;
    a=malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        *(a+i)= strtol (*(argv+i+1), &ep, 10);
        if (*ep) {
            fprintf (stderr, "Argument %d is not a number\n", i);
            return -1;
        }
    }
    sort (n);
    for (int i=0; i<n; i++)
        printf ("%d\n", *(a+i));
}
