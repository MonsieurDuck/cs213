#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "stringnode.h"
#include "loggingstringnode.h"

struct LoggingStringNode_class LoggingStringNode_class_table = {
  StringNode_compareTo,
  StringNode_printNode,
  LoggingStringNode_insert,
  Node_print,
  Node_delete,
};

void LoggingStringNode_insert(void* thisv, void* nodev) {
  struct StringNode* this = thisv;
  struct StringNode* node = nodev;

  printf("insert %s\n",node->s);
  StringNode_class_table.insert(this,node);
}


void* new_LoggingStringNode(char* l) {
  struct LoggingStringNode* obj = malloc(sizeof(struct StringNode));
  obj->class = &LoggingStringNode_class_table;
  StringNode_ctor(obj, l);
  return obj;
}

