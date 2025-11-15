#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_node {
  struct s_node *left;
  struct s_node *right;
  int data;
} t_node;

typedef struct s_qnode {
  int level;
  struct s_qnode *next;
  t_node *node;

} t_qnode;

typedef struct s_queue {
  t_qnode *front;
  t_qnode *rear;
} t_queue;

void bst_print(t_node *root);
t_node *bst_new(int value);

#endif
