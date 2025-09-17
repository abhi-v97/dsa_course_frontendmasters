#include <stdio.h>
#include <stdlib.h>

/* 
	The stack data structure is a linear structure that operates using a LIFO
	(Last In, First Out) principle.
	
	Search complexity:   O(n)
	Insert complexity:   O(1)
	Delete complexity:   O(1)
	Space complexity:    O(n)
*/

typedef struct	s_node
{
	int				data;
	struct s_node	*next;
}	t_node;

typedef struct	s_stack
{
	t_node	*head;
}	t_stack;

// mallocs and initialises an emtpy stack
// returns pointer to stack on success, NULL on failure
t_stack	*init_stack()
{
	t_stack	*new;

	new = (t_stack *) malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->head = NULL;
	return (new);
}

// pushes int data onto the stack
// returns 0 on success, 1 on failure
int	push(t_stack *stack, int data)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		return (1);
	node->data = data;
	node->next = NULL;
	if (!stack->head)
	{
		stack->head = node;
		return (1);
	}
	node->next = stack->head;
	stack->head = node;
	return (0);
}

// pops one element from the stack, sets *result to popped element on success
// returns 0 on success, 1 on failure
int	pop(t_stack *stack, int *result)
{
	t_node	*temp;

	if (!stack->head)
		return (1);
	temp = stack->head;
	stack->head = stack->head->next;
	if (result)
		*result = temp->data;
	free(temp);
	return (0);
}

// returns top element of stack on success
// returns 0 on success, 1 on failure
int	peek(t_stack *stack, int *result)
{
	if (!stack->head)
		return (1);
	if (result)
		*result = stack->head->data;
	return (0);
}

// prints stack, or an error message if the stack is empty
void	print_stack(t_stack *stack)
{
	t_node	*temp;

	if (!stack->head)
	{
		fprintf(stderr, "print: stack is empty\n");
		return ;
	}
	temp = stack->head;
	printf("{ ");
	while (temp)
	{
		printf("%i ", temp->data);
		temp = temp->next;
	}
	printf("}\n");
}

int	main()
{
	t_stack	*stack;
	int value;

	stack = init_stack();
	push(stack, 1);
	push(stack, 5);
	push(stack, 4);
	push(stack, 0);
	print_stack(stack);
	if (peek(stack, &value) == 0)
		printf("peek test: %i\n\n", value);
	else
	 	fprintf(stderr, "peek: stack is empty\n");
	
	pop(stack, NULL);
	print_stack(stack);
	if (peek(stack, &value) == 0)
		printf("peek test: %i\n\n", value);
	else
	 	fprintf(stderr, "peek: stack is empty\n");
	
	pop(stack, NULL);
	pop(stack, NULL);
	pop(stack, NULL);
	print_stack(stack);
	if (peek(stack, &value) == 0)
		printf("peek test: %i\n\n", value);
	else
	 	fprintf(stderr, "peek: stack is empty\n");
}
