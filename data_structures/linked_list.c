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
}	t_list;

t_list	*new_node(int data)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	new->data = data;
	new->next = NULL;
	return (new);
}

t_list	*get_last(t_list *head)
{
	t_list	*last;

	last = head;
	while (last && last->next != NULL)
		last = last->next;
	return (last);
}

void	append(t_list **head, int data)
{
	t_list	*new;

	new = new_node(data);
	if (!head)
		return ;
	else if (!(*head))
		*head = new;
	else
		get_last(*head)->next = new;
}

void	prepend(t_list **head, t_list *node)
{
	if (head)
		node->next = *head;
	*head = node;
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
	if (!current)
		return ;
	if (prev)
		prev->next = current->next;
	else
	 	*head = current->next;
	free(current);
	current = NULL;
}

void	remove_node(t_list **head, t_list *node)
{
	t_list	*current;
	t_list	*prev;
	
	current = *head;
	while (current != node)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
	{
		printf("node not found!\n");
		return ;
	}
	prev->next = current->next;
	current->next = NULL;
	free(current);
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

int main()
{
	int array[] = {0, 4, 5,1};
	t_list	*list;

	printf("\ntest linked list creation and append\n");
	list = NULL;
	for (int i = 0; i < 4; i++)
		append(&list, array[i]);
	print_list(list);

	printf("\ntest prepend\n");
	prepend(&list, new_node(99));
	print_list(list);

	printf("\ntest get_length\n");
	printf("list length: %i\n", get_length(list));

	printf("\ntest get\n");
	t_list *test = get(list, 3);
	printf("data at index 3: %i\n", test->data);
	
	printf("\ntest remove_node by removing the node found by get\n");
	remove_node(&list, test);
	print_list(list);

	for (int i = 0; i < 2; i ++)
		remove_at(&list, 0);
	print_list(list);
}
