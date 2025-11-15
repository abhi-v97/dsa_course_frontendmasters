#include "bst.h"

/**
 *
 * simple bst print function which outputs the bst tree in terms of level order.
 */
t_queue *queue_init() {
  t_queue *new;

  new = (t_queue *)malloc(sizeof(t_queue));
  new->front = NULL;
  new->rear = NULL;
  return (new);
}

void enqueue(t_queue *q, t_node *node, int level) {
  t_qnode *temp = (t_qnode *)malloc(sizeof(t_qnode));

  if (!temp)
    return;
  temp->node = node;
  temp->level = level;
  temp->next = NULL;

  if (q->rear == NULL) {
    q->front = temp;
    q->rear = temp;
    return;
  }
  q->rear->next = temp;
  q->rear = temp;
}

t_qnode *dequeue(t_queue *q) {
  if (q->front == NULL)
    return (NULL);

  t_qnode *temp;

  temp = q->front;
  q->front = q->front->next;
  if (q->front == NULL) {
    q->rear = NULL;
  }
  return (temp);
}

int bst_height(t_node *root, int h) {
  if (root == NULL) {
    return h - 1;
  }
  int left_height = bst_height(root->left, h + 1);
  int right_height = bst_height(root->right, h + 1);

  return (left_height > right_height ? left_height : right_height);
}

void bst_print(t_node *root) {
  t_queue *q = queue_init();

  enqueue(q, root, 0);

  int lastLevel = 0;
  int height = bst_height(root, 0);

  while (q->front != NULL) {
    t_qnode *top = dequeue(q);
    t_node *node = top->node;
    int topLevel = top->level;
    free(top);

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
