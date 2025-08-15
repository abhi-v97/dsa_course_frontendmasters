#include <stdio.h>

/* 
	Linear search is the simplest method of searching. Check each element of list
	sequentially until a match is found or you reach the end of the list.

	Returns the position array where the "needle" was found, since the value is
	already known and the array position is more useful than a true/false.

	Worst-case complexity: O(n)
	Average complexity: O(n)
	Best-case scenario: O(1)
*/
int	linear_search(int *haystack, int needle, int size)
{
	for (int i = 0; haystack[i] != 0; i++)
		if (haystack[i] == needle)
			return (i);
	return (-1);
}

int	main(void)
{
	int array[5] = {34, 21, 99, 78, 42};
	int needle = 78;
	int result = linear_search(array, needle, 5);

	if (result >= 0)
		printf("found needle %i in haystack at position %i\n", needle, result);
	else
		printf("needle %i not found\n", needle);
	return (0);
}
