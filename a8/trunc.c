#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"
//#include"list.c"

void print (element_t ev) {
    char* e = ev;
    if (e!=NULL)
    printf("%s\n",e);
    else printf("NULL\n");
}

void printInt(element_t ev){
    int* i=ev;
    printf("%d\n",*i);
}


void changeStrToNeg(element_t* rv, element_t av){
    int** r = (int**)rv;
    char* a = (char*)av;
    char* endptr;
    *r= malloc(sizeof(int*));
    **r = strtol(av,&endptr,10);
    if(**r==0)
    **r = -1;
}
                                //string     //int
void combineSI(element_t* rv, element_t av, element_t bv){
    char *a = av;
    char**r = (char**) rv;
    int* b= bv;
//    *r = malloc(sizeof(char*));
    if (*b!=-1)
        *r = NULL;
    else *r=a;
}
                                //string     //int
void remainFir(element_t* rv, element_t av, element_t bv ){
    char *a = av;
    char**r = (char**) rv;
    int* b= bv;
//    *r = malloc(sizeof(char));
    *r=a;
    if(strlen(a)>*b)
    a[*b] = '\0';
    
//    strcpy(*r,a);
}

int isPos(element_t av){
    int *a = av;
    return (*a != -1);
}



int isNull(element_t av){
    char *a = (char*) av;
    return (a != NULL);
    
}

                          //string     //string
void link(element_t* rv, element_t av, element_t bv){
    char *a = av;
    char**r = (char**) rv;
    char* b= bv;
    if(*r==NULL){
       *r = malloc(sizeof(char));}
       *r = realloc(*r,strlen(a)+strlen(b)+2);
    strcat(*r," ");
    strcat(*r,b);
//       *r = strcat(a,strcat(b," "));

}

int findMax(struct list* list){
    int temp=0;
    if (list_len(list)==0)
        return temp;
        else{
            temp= *(int*)list_get(list,0);
            while(list_len(list)>1){
                if(*(int*)list_get(list,0)<=*(int*)list_get(list,1)){ 
                temp= *(int*)list_get(list,1);
                list_remove(list,0);
                 }else {
                 temp= *(int*)list_get(list,0);
                 list_remove(list,1); 
            }
    }
        return temp;
}
}




int main(int argc, char** argv){
    struct list* l0 = list_create();
    for(int i=1;i<argc;i++){
        list_append(l0,argv[i]);
    }   
    
//    list_foreach(print,l0);
//Step1 finish here

 

    struct list* l1 = list_create();

    list_map1(changeStrToNeg,l1,l0);

//    list_foreach(printInt,l1);
//Step2 finish here



    struct list* l2 = list_create();
    list_map2(combineSI,l2,l0,l1);
//    list_foreach(print,l2);
//Step3 finish here



    struct list* l3 = list_create();
    list_filter(isPos,l3,l1);
   // list_foreach(printInt,l3);
//Step4 finish here



    struct list* l4 = list_create();
    list_filter(isNull,l4,l2);
//   list_foreach(print,l4);
//Step5 finish here

    struct list* l5 = list_create();
    list_map2(remainFir,l5,l4,l3);
//Step6 finish here

    list_foreach(print,l5);

//step7 finish here
    
    char* sp = malloc(sizeof(char));
  *sp=0;
  char** ptr =&sp;
    list_foldl (link, (element_t*) ptr, l5);
    printf ("%s\n", sp);
    free(sp);
//step8 finish here

   printf("%d\n", findMax(l3));



  list_foreach(free,l1);
//   list_foreach(free,l2);
//list_foreach(free,l5);
    list_destroy(l0);
    list_destroy(l1);
    list_destroy(l2);
    list_destroy(l3);
  //   list_foreach(print,l4);
    list_destroy(l4);
  //       list_foreach(print,l5);
     list_destroy(l5);

   }
