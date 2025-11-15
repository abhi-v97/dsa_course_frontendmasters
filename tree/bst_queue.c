#include "bst.h"

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

void queue_clear(t_queue *q) {
  t_qnode *temp;
  t_qnode *current;

  if (!q)
    return;
  temp = q->front;
  while (temp != NULL) {
    current = temp;
    temp = temp->next;
    free(current);
  }
  free(q);
}
