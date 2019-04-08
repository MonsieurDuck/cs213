#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "stringnode.h"
#include "reversestringnode.h"


struct ReverseStringNode_class ReverseStringNode_class_table = {
  ReverseStringNode_compareTo,
  StringNode_printNode,
  Node_insert,
  Node_print,
  Node_delete,
};


int ReverseStringNode_compareTo(void* thisv, void* nodev) {
    struct ReverseStringNode* this = thisv;
    struct ReverseStringNode* node = nodev;
    if(strcmp (this->s, node->s) < 0)
    return 1;
    else if(strcmp (this->s, node->s) > 0)
    return -1;
    else return 0;
}

void* new_ReverseStringNode(char* r) {
  struct ReverseStringNode* obj = malloc(sizeof(struct StringNode));
  obj->class = &ReverseStringNode_class_table;
  StringNode_ctor(obj, r);
  return obj;
}

