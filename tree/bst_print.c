#include "bst.h"

/**
 *
 * simple bst print function which outputs the bst tree in terms of level order.
 */
void bst_print(t_node *root) {
  t_queue *q = queue_init();

  enqueue(q, root, 0);

  int lastLevel = 0;
  int height = bst_height(root, 0);

  while (q->front != NULL) {
    t_qnode *top = dequeue(q);
    t_node *node = top->node;
    int topLevel = top->level;

    if (topLevel > lastLevel) {
      printf("\n");

      lastLevel = topLevel;
    }

    if (topLevel > height)
      break;

    if (node->data != -1)
      //   printf("N ");
      // else
      printf("%d ", node->data);

    if (node->data == -1)
      continue;

    if (node->left != NULL)
      enqueue(q, node->left, topLevel + 1);

    if (node->right != NULL)
      enqueue(q, node->right, topLevel + 1);
  }
}
