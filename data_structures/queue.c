#include <stdlib.h>
#include <stdio.h>

/* 
	Queues are a linear data structure that follow FIFO (first in first out)
	order of insertion and deletion.
	
	Here, queues are implemented using a linked list, but they can also be done 
	using arrays. 
	
	Compared to linked lists, since the operations primarily use the head or
	tail and they are stored and can be easily accessed, the time complexity
	for performing operations on the head or tail are O(1).
*/

typedef struct s_node
{
	struct s_node	*next;
	int				value;
}	t_node;

typedef struct s_queue
{
	struct s_node *head;
	struct s_node *tail;
}	t_queue;

t_queue	*init_queue()
{
	t_queue	*new;

	new = (t_queue *) malloc(sizeof(t_queue));
	new->head = NULL;
	new->tail = NULL;
	return (new);
}

void	enqueue(t_queue *q, int value)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node));
	new->value = value;
	if (!q->tail)
	{
		q->tail = new;
		q->head = new;
		return ;
	}
	q->tail->next = new;
	q->tail = new;
}

void	dequeue(t_queue *q)
{
	t_node	*temp;

	if (!q)
		return ;
	temp = q->head;
	q->head = temp->next;
	free(temp);
}

int	peek(t_queue *q)
{
	if (!q || !q->head)
		return (printf("error, queue is empty\n"), 0);
	return (q->head->value);
}

void	print_queue(t_queue *q)
{
	t_node	*temp;

	if (!q || !q->head)
		return ;
	temp = q->head;
	printf("{ ");
	while (temp)
	{
		printf("%i ", temp->value);
		temp = temp->next;
	}
	printf("}\n");
}

int	main()
{
	t_queue	*q;
	
	q = init_queue();
	enqueue(q, 0);
	enqueue(q, 4);
	enqueue(q, 5);
	enqueue(q, 1);
	print_queue(q);
	dequeue(q);
	dequeue(q);
	print_queue(q);
	printf("test peek: %i\n", peek(q));
}
