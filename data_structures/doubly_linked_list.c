#include <stdlib.h>
#include <stdio.h>

/* 
	Linked lists are a linear data structure where each element (node) is
	connect to the next node using pointers. Unlike arrays, linked lists are
	stored in random memory locations.

	Linked lists usually have O(1) complexity unless you need to append ore remove 
	an element in the middle of the list, then you need to traverse it which 
	changes the complexity to O(N).
*/

typedef struct s_list
{
	int				data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

t_list	*new_node(int data)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	prepend(t_list **head, int data)
{
	t_list	*new;

	if (!head)
		return ;
	new = new_node(data);
	if (!*head)
		*head = new;
	else
	{
		new->next = *head;
		(*head)->prev = new;
		*head = new;
	}
}

void	append(t_list **head, int data)
{
	t_list	*new;
	t_list	*temp;

	if (!head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	new = new_node(data);
	temp->next = new;
	new->prev = temp;
}


int	get_length(t_list *head)
{
	int		size;
	t_list	*temp;

	size = 0;
	temp = head;
	while (temp)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}

t_list	*get(t_list *head, int index)
{
	t_list	*node;
	int		i;

	i = -1;
	node = head;
	while (node && ++i < index)
		node = node->next;	
	return (node);
}

void	remove_node(t_list **head, t_list *node)
{
	t_list	*left;
	t_list	*right;

	if (!head || !node)
		return ;
	left = node->prev;
	right = node->next;
	if (node == *head)
		*head = (*head)->next;
	if (left)
		left->next = right;
	if (right)
		right->prev = left;
	node->next = NULL;
	node->prev = NULL;
	free(node);
}

void	remove_at(t_list **head, int index)
{
	int		i;
	t_list	*current;
	t_list	*prev;

	i = -1;
	current = *head;
	prev = NULL;
	if (!get_length(*head) || get_length(*head) < index)
	{
		printf("index out of bounds!\n");
		return ;
	}
	while (current && ++i < index)
	{
		prev = current;
		current = current->next;
	}
	remove_node(head, current);
}

void	insert_at(t_list **head, t_list *node, int index)
{
	int		i;
	t_list	*current;

	i = -1;
	if (get_length(*head) < index)
	{
		printf("index too large\n");
		return ;
	}
	if (!(*head) && index == 0)
		*head = node;
	else
	{
		current = *head;
		while (++i < index - 1)
			current = current->next;
		node->next = current->next;
		if (current->next)
			current->next->prev = node;
		current->next = node;
	}
}

void	lst_map(t_list **head, int(*f)(t_list *))
{
	t_list	*temp;

	temp = *head;
	while (temp)
	{
		f(temp);
		temp = temp->next;
	}
}

void	print_list(t_list *head)
{
	t_list	*temp;

	temp = head;
	printf("{ ");
	while (temp)
	{
		printf("%i ", temp->data);
		temp = temp->next;
	}
	printf("}\n");
}
