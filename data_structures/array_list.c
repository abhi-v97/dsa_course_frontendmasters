#include <stdlib.h>
#include <stdio.h>

/* 
	An ArrayList is a data strcucture that is a dynamically resizing array,
	allows you to have the benefits of an array while being flexible in size.
	
	If you add or remove elements from the middle of the list or the start, you
	have shift all elements around, which leads to a complexity of O(n).

	However, if you know the index and want to get the result, like an array
	you can access the element easily with O(1) complexity.

	Complexities:
	append: O(1)
	prepend: O(n)
	insert: O(n)
	remove: O(n)
	get: O(1)
*/
typedef struct s_array_list
{
	int		len;
	int		size;
	int		*array;
}			t_array_list;

t_array_list	*array_list_init()
{
	t_array_list *new;

	new = (t_array_list *) malloc(sizeof(t_array_list));
	new->size = 0;
	new->len = 0;
	new->array = NULL;
	return (new);
}

void	array_list_append(t_array_list *head, int value)
{
	if (head->len == head->size)
	{
		if (head->size == 0)
			head->size++;
		head->size *= 2;
		head->array = realloc(head->array, sizeof(head->array[0]) * (head->size + 1));
	}
	if (head->array)
	{
		head->array[head->len] = value;
		head->len++;
	}
}

void	array_list_insert(t_array_list *list, int value, int index)
{
	if (index < 0 || index >= list->size)
	{
		printf("invalid index\n");
		return ;
	}
	if (list->size == 0 && index == 0)
	{
		array_list_append(list, value);
		return ;
	}
	for (int i = list->size; i > index; i--)
		list->array[i] = list->array[i - 1];
	list->array[index] = value;
	list->size++;
}

// shift all elements to the left at the index
void	array_list_remove(t_array_list *list, int index)
{
	if (list->size == 0)
	{
		printf("empty list\n");
		return ;
	}
	if (index < 0 || index >= list->size)
	{
		printf("invalid index\n");
		return ;
	}
	for (int i = index; i < list->size; i++)
		list->array[i] = list->array[i + 1];
	list->size--;
}

void	array_list_remove_at(t_array_list *list, int value)
{
	int	index;

	index = -1;
	for (int i = 0; i < list->size; i++)
	{
		if (list->array[i] == value)
		{
			index = i;
			break;
		}
	}
	if (index < 0)
	{
		printf("value not found!\n");
		return ;
	}
	array_list_remove(list, index);
}

int		array_list_get(t_array_list *list, int index)
{
	if (index < list->size)
		return (list->array[index]);
	else
	 	return (-1);
}

void	array_list_print(t_array_list *list)
{
	if (list->size == 0)
		printf("Empty array\n");
	printf("{ ");
	for (int i = 0; i < list->size; i++)
		printf("%i ", list->array[i]);
	printf("}\n");
}

int	main()
{
	t_array_list *list;

	list = array_list_init();

	array_list_append(list, 0);
	array_list_append(list, 4);
	array_list_append(list, 5);
	array_list_append(list, 1);
	array_list_print(list);
	

	printf("get value at index 3: %i\n", array_list_get(list, 3));
	array_list_remove(list, 1);
	array_list_print(list);
	
	array_list_insert(list, 99, 1);
	array_list_print(list);
}