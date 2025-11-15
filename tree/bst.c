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

t_node *getSuccessor(t_node *current) {
  current = current->right;
  while (current && current->left) {
    current = current->left;
  }
  return (current);
}

// delete node in bst with int value
// to delete a node while maintaining the bst structure, the deletion considers
// how many children the node to be deleted has
//
// - if its a leaf node, it can simply be deleted as it has no children to
// maintain
// - if it has one child, it is connected to the node's parent and then the
// target node is removed
// - if it has two children, the node has to be replaced with a successor
// -- inorder successor: smallest value in the right subtree, next greater value
// than target node
// -- inorder predecessor: largest value in the left subtree, next smallest
// value than target node
t_node *bst_delete(t_node **root, int value) {
  if (root == NULL || *root == NULL)
    return (*root);

  t_node *node = *root;

  if (node->data > value)
    node->left = bst_delete(&node->left, value);
  else if (node->data < value)
    node->right = bst_delete(&node->right, value);
  else {
    if (node->left == NULL) {
      t_node *temp = node->right;
      free(node);
      return (temp);
    }
    if (node->right == NULL) {
      t_node *temp = node->left;
      free(node);
      return (temp);
    }

    t_node *successor = getSuccessor(node);
    node->data = successor->data;
    node->right = bst_delete(&node->right, successor->data);
  }
  return (node);
}

void bst_free(t_node *root) {
  if (root == NULL)
    return;

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
  bst_insert(root, 3);
  bst_print(*root);

  bst_delete(root, 4);
  bst_print(*root);
  bst_free(*root);
  free(root);
  return (0);
}
