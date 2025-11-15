#include "bst.h"

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

// creates a new tree node and initialises it
t_node *bst_new(int value) {
  t_node *new;

  new = (t_node *)malloc(sizeof(t_node));
  new->left = NULL;
  new->right = NULL;
  new->data = value;
  return (new);
}

// since the left node of a tree is always smaller, the leftmost node with a
// null left branch will be the smallest each time
//
// Complexity: O(h) time, O(1) space
int bst_min(t_node *root) {
  if (root == NULL)
    return (-1);

  while (root->left)
    root = root->left;

  return (root->data);
}

// Opposite of bst_min, the rightmost value of a tree has to be its max
//
// Complexity: O(h) time, O(1) space
int bst_max(t_node *root) {
  if (root == NULL)
    return (-1);

  while (root->right)
    root = root->right;

  return (root->data);
}

// inserts a node into tree using recursion
void bst_insert(t_node **root, int value) {
  // base case
  if (root == NULL || *root == NULL) {
    *root = bst_new(value);
  }

  t_node *node = *root;
  // choose which branch of the tree to walk towards
  if (value < node->data) {
    if (node->left) {
      bst_insert(&node->left, value);
    } else {
      node->left = bst_new(value);
    }

  } else if (value > node->data) {
    if (node->right) {
      bst_insert(&node->right, value);
    } else {
      node->right = bst_new(value);
    }
  }
}

// inserts node into tree iteratively
//
// start from root, go left if value is smaller, right if greater
// Complexity: O(h) time, O(h) space due to recursion stack
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
void bst_inorder_print(t_node *root) {
  if (root == NULL)
    return;

  bst_inorder_print(root->left);
  printf("%i ", root->data);
  bst_inorder_print(root->right);
}

// helper function for bst_delete
// searches for smallest value in right subtree, the next greater value than the
// target node to be deleted
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

// finds the next element from inorder traversal (inorder successor)
//
// since the number can be in a separate branch, we start from the top and keep
// filtering
//
// if we encounter a larger node, it is marked as a possible successor and
// proceed to its left, trying to find the next smallest node
// if we encounter a smaller or equal node, we move towards the left branch of
// the tree
// Complexity: O(h) time, O(1) space due to iterative approach
t_node *bst_inorder_next(t_node *root, int target) {
  if (root == NULL)
    return (NULL);

  t_node *next = NULL;
  t_node *current = root;

  while (current) {
    if (current->data > target) {
      next = current;
      current = current->left;
    } else if (current->data <= target) {
      current = current->right;
    }
  }

  return (next);
}

void bst_free(t_node *root) {
  if (root == NULL)
    return;

  bst_free(root->left);
  bst_free(root->right);
  free(root);
}

// hacky bst print that outputs a tree-like structure
// start the function with a large value for i like 10
// this adds a bunch of whitespace to root, which is then subtracted for left
// nodes and added for right nodes, mimicking a tree structure
void bst_print_simple(t_node *root, int i) {

  int j = 0;

  if (root == NULL)
    return;

  while (j++ < i)
    printf("   ");
  printf("%d\n", root->data);
  bst_print_simple(root->left, --i);
  bst_print_simple(root->right, i + 2);
}

int main(int argc, char **argv) {
  t_node **root;

  root = (t_node **)malloc(sizeof(t_node *));
  *root = NULL;
  if (!root)
    return (1);
  bst_insert(root, 22);
  bst_insert(root, 12);
  bst_insert(root, 30);
  bst_insert(root, 8);
  bst_insert(root, 20);
  bst_insert(root, 40);
  bst_insert(root, 15);
  bst_print_simple(*root, 10);

  bst_free(*root);
  free(root);

  return (0);
}
