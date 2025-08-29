#include <stdlib.h>
#include <stdio.h>

/* 
	Circular buffer: FIFO data structure where the memory is stored in a loop.

	This is done using two pointers to the array, the head and tail pointers.
	When data is written, the head pointer is incremented, and when data is
	removed, the tail pointer is incremented.
	
	A common issue in ring buffers is differentiating between full and empty,
	as head and tail are equal in both scenarios. In this implementation, the
	array will use N - 1 elements to solve this issue. If the head and tail
	pointers are equal, the buffer is empty. If (head + 1) equals tail, the
	buffer is full.

	Another solution would be to use a bool to differentiate between empty and
	full.
*/
typedef struct s_ring_buf
{
	int			*array;
	int			head;
	int			tail;
	int			max_size;
}				t_ring_buf;

t_ring_buf	*ring_buf_init()
{
	t_ring_buf	*new;
	
	new = (t_ring_buf *) malloc(sizeof(t_ring_buf));
	if (!new)
		return (NULL);
	new->head = 0;
	new->tail = 0;
	new->max_size = 2;
	new->array = (int *) malloc(sizeof(int) * (new->max_size + 1));
	return (new);
}

void	ring_buf_extend(t_ring_buf *list)
{
	int		*new;
	int		temp_head;
	int		i;

	list->max_size *= 2;
	new = (int *) malloc(sizeof(int) * (list->max_size + 1));
	temp_head = list->head;
	i = 0;
	while ((temp_head % list->max_size) != list->tail)
	{
		new[i] = list->array[temp_head];
		temp_head++;
		i++;
	}
	free(list->array);
	list->array = new;
	list->head = i;
	list->tail = 0;
}

int		ring_buf_push(t_ring_buf *list, int value)
{
	int		next;
	
	next = list->head + 1;
	if (next >= list->max_size)
		next = 0;
	if (next == list->tail)
		ring_buf_extend(list);
	list->array[list->head] = value;
	list->head = list->head + 1;
	return (0);
}

int		ring_buf_pop(t_ring_buf *list)
{
	int		next;
	int		result;

	if (list->head == list->tail)
		return (-1);
	next = list->tail + 1;
	if (next >= list->max_size)
		next = 0;
	result = list->array[list->tail];
	list->tail = next;
	return (result);
}

void	ring_buf_print(t_ring_buf *list)
{
	int		temp;

	temp = list->tail;
	printf("{ ");
	while ((temp % list->max_size) != list->head)
	{
		printf("%i ", list->array[temp++]);
	}
	printf("}\n");
}

int main()
{
	t_ring_buf *list;

	list = ring_buf_init();
	ring_buf_push(list, 0);
	ring_buf_push(list, 4);
	ring_buf_push(list, 5);
	ring_buf_push(list, 1);
	ring_buf_print(list);
}
