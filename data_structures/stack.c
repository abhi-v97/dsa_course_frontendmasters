#include <stdio.h>
#include <stdlib.h>

typedef struct	s_node
{
	int				data;
	struct s_node	*next;
}	t_node;

typedef struct	s_stack
{
	t_node	*head;
}	t_stack;

t_stack	*init_stack()
{
	t_stack	*new;

	new = (t_stack *) malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->head = NULL;
	return (new);
}

void	push(t_stack *stack, int data)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		return ;
	node->data = data;
	node->next = NULL;
	if (!stack->head)
	{
		stack->head = node;
		return ;
	}
	node->next = stack->head;
	stack->head = node;
}

int	pop(t_stack *stack)
{
	t_node	*temp;
	int		value;

	if (!stack->head)
	{
		printf("Stack underflow\n");
		return (-1);
	}
	temp = stack->head;
	stack->head = stack->head->next;
	value = temp->data;
	free(temp);
	return (value);
}

int	peek(t_stack *stack)
{
	if (!stack->head)
	{
		printf("Stack is empty\n");
		return (-1);
	}
	return (stack->head->data);
}

void	print_stack(t_stack *stack)
{
	t_node	*temp;

	if (!stack->head)
	{
		printf("Stack is empty\n");
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

	stack = init_stack();
	push(stack, 1);
	push(stack, 5);
	push(stack, 4);
	push(stack, 0);
	print_stack(stack);
	printf("peek test: %i\n\n", peek(stack));
	
	pop(stack);
	print_stack(stack);
	printf("peek test: %i\n\n", peek(stack));
	
	pop(stack);
	pop(stack);
	pop(stack);
	print_stack(stack);
	printf("peek test: %i\n\n", peek(stack));
}
