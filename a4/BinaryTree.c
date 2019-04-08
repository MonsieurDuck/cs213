#include <stdlib.h>
#include <stdio.h>

/**
 * A node of the binary tree containing the node's integer value
 * and pointers to its right and left children (or null).
 */
struct Node* n1;

struct Node {
  int value;
  struct Node* left;
  struct Node* right;
};

/**
 * Create a new node with no children.
 */
struct Node* create (int value) {
  struct Node* n1;
  n1 = malloc(sizeof(struct Node));
  n1->value=value;
  n1->left=NULL;
  n1->right=NULL;
  return n1;
}

/**
 * Insert the node n into the binary tree rooted by toNode.
 */
void insert (struct Node* toNode, struct Node* n) {
  if (n->value <= toNode->value)
  {
    if (toNode->left == NULL)
      toNode->left= n;
    else
      insert(toNode->left,n);
    }
    else{
      if (toNode->right == NULL)
        toNode->right=n;
      else
        insert(toNode->right,n);
  }
}

/**
 * Print the contents entire binary tree in order of ascending integer value.
 */
void printInOrder (struct Node* node) {
  if (node->left != NULL)
  {
    printInOrder(node->left);
  } 
  printf("%d\n", node->value);
  if (node->right != NULL)
  {
    printInOrder(node->right);
  }
}

/**
 * Create a new tree populated with values provided on the command line and
 * print it in depth-first order.
 */
int main (int argc, char* argv[]) {
//   struct Node* root;

//   // read values from command line and add them to the tree
//   if (argc==0)
//   {
//     root = create(100);
//     insert(root,create(50));
//     insert(root,create(150));
//   }
//   else{
//   for (int i=1; i<argc; i++) {
//     int value = atoi (argv [i]);
//     struct Node* n2= create(value);
//     if (root != NULL)
//       root=n2;
//     else
//       insert(root,n2);
//     printf ("%d\n", value);
//   }
// }
// if (root != NULL)
//   printInOrder(root);

  struct Node* root = NULL;
  for (int i=1; i<argc; i++) {
    int value = atoi (argv [i]);
    struct Node* n2= create(value);
    if (root == NULL)
      root=n2;
    else
      insert(root,n2);
  }
 if (root != NULL)
   printInOrder(root);

}