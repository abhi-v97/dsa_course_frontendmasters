#include "bst.h"

t_node *bst_breadth_first(t_node *root, int needle) {
  t_queue *q;
  int height;

  q = queue_init();
  height = bst_height(root, 0);
  enqueue(q, root, 0);
  while (q->front != NULL) {
    t_qnode *top = dequeue(q);
    t_node *node = top->node;

    if (node->data == needle)
      return (node);

    if (node->left != NULL)
      enqueue(q, node->left, 0);

    if (node->right != NULL)
      enqueue(q, node->right, 0);
  }
  return (NULL);
}

// helper function which returns bst height, used for breadth first traversal
int bst_height(t_node *root, int h) {
  if (root == NULL) {
    return h - 1;
  }
  int left_height = bst_height(root->left, h + 1);
  int right_height = bst_height(root->right, h + 1);

  return (left_height > right_height ? left_height : right_height);
}
