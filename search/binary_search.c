#include <stdio.h>

/* 
	Binary search: more efficient than linear search, but it requires a sorted list.
	You divide the list in half and compare the middle element. If you find the
	item you're looking for, you stop. If you didn't, you decide which half of
	the array to focus on, by comparing the middle element to the needle. 
	
	If the needle is smaller than the middle element, you search in the lower
	half of the array, and vice versa.

	Worst-case complexity: O(log n)
	Best-case scenario: O(1)
*/
int	binary_search(int *haystack, int needle, int size)
{
	int		low;
	int		mid;
	int		high;
	int		value;

	low = 0;
	high = size;

	while (low < high)
	{
		mid = low + (high - low) / 2;
		value = haystack[mid];
		if (value == needle)
			return (mid);
		else if (needle < value)
			high = mid;
		else if (needle > value)
			low = mid + 1;
	}
	return (-1);
}

int main()
{
	int array[8] = {3, 4, 11, 12, 23, 44, 54, 65};
	int needle = 23;
	int result = binary_search(array, needle, 8);
	if (result >= 0)
		printf("found needle %i in haystack at position %i\n", needle, result);
	else
		printf("needle %i not found\n", needle);
	return (0);
}
