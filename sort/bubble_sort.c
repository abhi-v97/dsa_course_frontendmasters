#include <stdbool.h>
#include <stdio.h>

/* 
	Simples sorting algorithm that compares neighbouring elements and swaps
	them if they are in the wrong order.
	The array is sorted in multiple passes. At the end of first pass, the last
	element is placed correctly. After the second pass, the second-to-last
	element is sorted correctly, and so on.
	This algorithm is not suitable for large data sets as its time complexity
	is high.

	The following implementation has a slight optimisation; if the inner loop
	never performs a swap operation, that means the list is now sorted and thus
	the outer loop is stopped.

	Worst-case complexity: O(n^2)
	Average complexity: O(n^2)
	Best-case scenario: O(n)
*/
void	bubble_sort(int *array, int size)
{
	int		temp;
	bool	swapped;

	for (int i = 0; i < size - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (array[j + 1] < array[j])
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				swapped = true;
			}
		}
		if (swapped == false)
			break ;
	}
}

int main()
{
	int array[] = {0, 4, 5,1};
	bubble_sort(array, 4);
	
	for (int i = 0; i < 4; i++)
		printf("%i ", array[i]);
	printf("\n");
	return (0);
}
