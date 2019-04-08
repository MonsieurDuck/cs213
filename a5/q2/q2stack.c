#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Element {
  char   name[200];
  struct Element *next;
};

struct Element *top = 0;

void push (char* aName) {
  struct Element* e = malloc (sizeof (*e));    // Not the bug: sizeof (*e) == sizeof(struct Element)
  strncpy (e->name, aName, sizeof (e->name));  // Not the bug: sizeof (e->name) == 200
  e->next  = top;
  top = e;

    
}

void pop(char* n,int size_n) {
  struct Element* e = top;
  top = e->next;
strncpy(n,e->name,size_n);
  free (e);
}

int main (int argc, char** argv) {
 char w[200],x[200],y[200],z[200];
  push ("A");
  push ("B");
  pop(w, 200);
  push ("C");
  push ("D");
  pop(x,200);
 pop(y,200);
  pop(z,200);
  printf ("%s %s %s %s\n", w, x, y, z);
}
