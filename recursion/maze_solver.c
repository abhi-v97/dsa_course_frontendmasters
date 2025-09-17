#include <stdio.h>
#include <stdbool.h>
// https://stackoverflow.com/questions/74130502/maze-solving-in-c

/* 
	A maze solver created to understand test recursion.

	When using recursion, define base cases for the scenario:
		1. pointer outside the map
		2. pointer points to a wall
		3. pointer is null
		4. pointer is "seen"
		
	Typically, you make a separate function for the recursion which is called
	by the "entrance" function
	
	When to use recursion: when simple for loops won't work; when there is a
	branching factor such as coordinates;
	
	Function prints map with the solution, if found
*/

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

t_point	find_start(char maze[5][5], char c)
{
	t_point result;

	result.x = -1;
	result.y = -1;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			if (maze[i][j] == c)
			{
				result.x = i;
				result.y = j;
				return (result);
			}
		}
	return (result);
}

void	map_setchar(char maze[5][5], char c)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			maze[i][j] = c;
}

bool	can_walk(char maze[5][5], char seen[5][5], int x, int y)
{
	if (x < 0 || y < 0 || x > 4 || y > 4)
		return (false);
	if (maze[x][y] == '1')
		return (false);
	if (seen[x][y] == true)
		return (false);
	seen[x][y] = true;
	return (false);
}

bool walk(char maze[5][5], int x, int y, char seen[5][5])
{
	if (maze[x][y] == 'E')
	{
		seen[x][y] = '1';
		return (true);
	}
	if (can_walk(maze, seen, x, y) == true)
	{
		seen[x][y] = '1';
		maze[x][y] = '1';
		for (int i = 0; i < 5; i++)
		{
			if (walk(maze, x + 1, y, seen) == true)
				return (true);
			if (walk(maze, x, y + 1, seen) == true)
				return (true);
			if (walk(maze, x - 1, y, seen) == true)
				return (true);
			if (walk(maze, x, y - 1, seen) == true)
				return (true);
			seen[x][y] = '0';
			maze[x][y] = '0';
		}
	}
	return (false);
}

void	print_solution(char maze[5][5], char seen[5][5], int height, int width)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (maze[y][x] == '0' && seen[y][x] == '1')
				printf(" x ");
			else
				printf(" %c ", maze[y][x]);
		}
		printf("\n");	
	}
}

void	solve(char maze[5][5])
{
	char	seen[5][5];
	char	path[5][5];
	t_point	start = find_start(maze, 'S');
	
	map_setchar(seen, '0');
	map_setchar(path, '0');
	
	if (walk(maze, start.x, start.y, seen) == true)
		print_solution(maze, seen, 5, 5);

	print_solution(maze, seen, 5, 5);
	print_solution(seen, seen, 5, 5);

}

int main()
{
	char map[5][5] = {{'1', '1', '1', '1', 'E'}, 
					{'1', '0', '0', '0', '0'}, 
					{'1', '0', '1', '1', '1'}, 
					{'1', '0', '1', '0', '1'}, 
					{'1', 'S', '1', '1', '1'}};
	solve(map);

}
