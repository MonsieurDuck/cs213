#include <stdlib.h>
#include <stdio.h>
int a[10];
int* s= &a;

void update(int b, int c){
    a[c]=a[c]+b;
}

void main(){
    update(3,4);
    update(1,2);
    for(int i=0;i<10;i++){
        printf("%d\n",a[i]);
    }
    
}
