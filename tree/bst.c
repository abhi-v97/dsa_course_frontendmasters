#include <stdio.h>
#include <stdlib.h>

/**
 * A binary search tree is a type of binary tree data structure where each node
 * is unique and satisifes the following conditions:
 *
 * - all nodes in the left subtree of a node are strictly less than the node.
 * - all nodes in the right subtree of the node are strictly greater.
 *
 * The tree structure allows for efficient search, insertion, and deletion, if
 * the tree remains balanced.
 */

typedef struct s_node {
  struct s_node *left;
  struct s_node *right;
  int data;
} t_node;

// creates a new tree node and initialises it
t_node *bst_new(int value) {
  t_node *new;

  new = (t_node *)malloc(sizeof(t_node));
  new->left = NULL;
  new->right = NULL;
  new->data = value;
  return (new);
}

// inserts a node into tree using recursion
void bst_insert(t_node **root, int value) {
  // base case
  if (root == NULL || *root == NULL) {
    *root = bst_new(value);
  }

  // choose which branch of the tree to walk towards
  if (value < (*root)->data) {
    if ((*root)->left) {
      bst_insert(&(*root)->left, value);
    } else {
      (*root)->left = bst_new(value);
    }

  } else if (value > (*root)->data) {
    if ((*root)->right) {
      bst_insert(&(*root)->right, value);
    } else {
      (*root)->right = bst_new(value);
    }
  }
}

// inserts node into tree iteratively
t_node *bst_insert_iter(t_node **root, int value) {
  t_node *new;

  if (root == NULL || *root == NULL) {
    *root = bst_new(value);
    return (*root);
  }
  new = *root;
  while (new != NULL) {
    if (new->left && value < new->data)
      new = new->left;
    else if (new->right && value > new->data)
      new = new->right;
    else
      break;
  }
  if (value < new->data)
    new->left = bst_new(value);
  else
    new->right = bst_new(value);
  return (new);
}

// prints the bst with in order traversal
void bst_print(t_node *root) {
  if (root == NULL)
    return;

  bst_print(root->left);
  printf("%i ", root->data);
  bst_print(root->right);
}

void bst_free(t_node *root) {
	if (root == NULL)
		return ;

	bst_free(root->left);
	bst_free(root->right);
	free(root);
}

int main(int argc, char **argv) {
  t_node **root;

  root = (t_node **)malloc(sizeof(t_node *));
  *root = NULL;
  if (!root)
    return (1);
  bst_insert(root, 4);
  bst_insert(root, 5);
  bst_insert(root, 0);
  bst_insert(root, 1);
  bst_print(*root);
  
  bst_free(*root);
  free(root);
  return (0);
}
