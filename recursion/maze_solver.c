#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
// https://stackoverflow.com/questions/74130502/maze-solving-in-c

/* 
	A maze solver created to understand and test recursion.

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
	// seen[x][y] = true;
	return (true);
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
			if (maze[y][x] == '1' && seen[y][x] == '1')
				printf(" x ");
			else
				printf(" %c ", maze[y][x]);
		}
		printf("\n");	
	}
}

void	solve(char maze[5][5], int width, int height)
{
	char	seen[5][5];
	t_point	start = find_start(maze, 'S');
	
	map_setchar(seen, '0');
	
	if (walk(maze, start.x, start.y, seen) == true)
	{
		maze[start.x][start.y] = 'S';
		print_solution(maze, seen, 5, 5);
	}
}

int	get_maze_height(char *file)
{
	FILE *fd = fopen(file, "r");
	char *line = NULL;
	size_t len = 0;
	int	height = 0;

	while (getline(&line, &len, fd) != -1)
		height++;
	return (fclose(fd), height);
}

int get_maze_width(char **maze)
{
	int width = 0;
	int temp = 0;
	int i = 0;

	while (maze[i])
	{
		temp = strlen(maze[i]);
		if (temp > width)
			width = temp;
		i++;
	}
	return (width);
}

int main()
{
	char map[5][5] = {{'1', '1', '1', '1', 'E'}, 
					{'1', '0', '0', '0', '0'}, 
					{'1', '0', '1', '1', '1'}, 
					{'1', '0', '1', '0', '1'}, 
					{'1', 'S', '1', '1', '1'}};
	
	char **maze;
	int	height;

	height = get_maze_height("maze");
	maze = (char **) malloc(sizeof(char *) * (height + 1));
	maze[height] = NULL;
	
	
	FILE *fd = fopen("maze", "r");
	char *line = NULL;
	size_t len = 0;
	int i = 0;
	while (getline(&line, &len, fd) != -1)
	{
		maze[i] = strdup(line);
		i++;
	}

	int width = get_maze_width(maze);
	solve(map, width, height);

}
