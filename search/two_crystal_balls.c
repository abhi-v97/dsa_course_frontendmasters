#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* 
	Given two crystal balls and a 100 floor building, find the maximum height
	from which a ball can be dropped without breaking.
	
	To optimise the search, we "jump" a certain amount of floors instead of
	checking one by one. Once we find that it breaks, now we check one by one
	until we find the exact floor.

	This results in us checking for a max (n / jump_amount) + jump_amount
	times. The optimal number for jump amount is √n, as most other solutions
	scale linearly with increasing size. Compare the graph of y = x with y =
	x/2, sure the gradient has changed but its still linear, and increasing
	with size. The graph of y = √x however is a decreasing function. 
	
	Worst-case complexity: O(√n)
	Best case scenario: O(1)
*/
int	two_crystal_balls(bool *floors, int size)
{
	int		jump_amount;
	int		i;
	
	jump_amount = sqrt(size);
	i = jump_amount;
	for (; i < size; i += jump_amount)
	{
		if (floors[i] == true)
			break ;
	}
	for (int j = i - jump_amount; j < size; j++)
	{
		if (floors[j] == true)
			return (j);
	}
	return (-1);
}

// run with cc -lm two_crystal_balls.c
int main()
{
	int		result;

	printf("6th floor (assuming 0 is ground floor)\n");
	bool test[10] = {false, false, false, false,
		false, false, true, true, true, true};
	result = two_crystal_balls(test, 10);
	printf("result = %i\n\n", result);

	printf("test for when balls never break)\n");
	bool test2[5] = {false, false, false, false, false};
	result = two_crystal_balls(test2, 10);
	printf("result = %i\n\n", result);

	printf("ground floor test)\n");
	bool test3[5] = {true, true, true, true, true};
	result = two_crystal_balls(test3, 10);
	printf("result = %i\n\n", result);
	return (0);
}
