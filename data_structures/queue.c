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

// mallocs and initialises an empty queue
// returns pointer to stack on success, NULL on failure
t_queue	*init_queue()
{
	t_queue	*new;

	new = (t_queue *) malloc(sizeof(t_queue));
	if (!new)
		return (NULL);
	new->head = NULL;
	new->tail = NULL;
	return (new);
}

// adds value as a new node in the queue
// returns 0 on success, 1 on failure
int	enqueue(t_queue *q, int value)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node));
	if (!new)
		return (1);
	new->value = value;
	if (!q->tail)
	{
		q->tail = new;
		q->head = new;
	}
	else
	{
		q->tail->next = new;
		q->tail = new;
	}
	return (0);
}

// removes an element from the queue
// updates *value with the removed element
// returns 0 on success, 1 on failure
int	dequeue(t_queue *q, int *value)
{
	t_node	*temp;

	if (!q)
		return (1);
	temp = q->head;
	if (value)
		*value = temp->value;
	q->head = temp->next;
	free(temp);
	return (0);
}

// updates *value to head of queue on success
// returns 0 on success, 1 on failure
int	peek(t_queue *q, int *value)
{
	if (!q || !q->head)
		return (1);
	if (value)
		*value = q->head->value;
	return (0);
}

// prints queue, or an error message if it is empty
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
	int		value;
	
	q = init_queue();
	enqueue(q, 0);
	enqueue(q, 4);
	enqueue(q, 5);
	enqueue(q, 1);
	print_queue(q);
	dequeue(q, NULL);
	dequeue(q, NULL);
	print_queue(q);
	peek(q, &value);
	printf("test peek: %i\n", value);
}
