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

t_point	find_start(char **maze, char c, int width, int height)
{
	t_point start;

	start.x = -1;
	start.y = -1;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			if (maze[i][j] == c)
			{
				start.x = j;
				start.y = i;
				return (start);
			}
		}
	return (start);
}

bool	can_walk(char **maze, char **seen, int x, int y, int width, int height)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return (false);
	if (maze[y][x] == '1')
		return (false);
	if (seen[y][x] == true)
		return (false);
	return (true);
}

bool walk(char **maze, char **seen, int x, int y, int width, int height)
{
	if (maze[y] && maze[y][x] == 'E')
	{
		seen[y][x] = '1';
		return (true);
	}
	if (can_walk(maze, seen, x, y, width, height) == true)
	{
		seen[y][x] = '1';
		maze[y][x] = '1';
		for (int i = 0; i < 5; i++)
		{
			if (walk(maze, seen, x, y + 1, width, height) == true)
				return (true);
			if (walk(maze, seen, x + 1, y, width, height) == true)
				return (true);
			if (walk(maze, seen, x, y - 1, width, height) == true)
				return (true);
			if (walk(maze, seen, x - 1, y, width, height) == true)
				return (true);
			seen[y][x] = '0';
			maze[y][x] = '0';
		}
	}
	return (false);
}

void	print_solution(char **maze, char **seen, int width, int height)
{
	for (int y = 0; y < height && maze[y]; y++)
	{
		for (int x = 0; x < width && maze[y][x]; x++)
		{
			if (maze[y][x] == '1' && seen[y][x] == '1')
				printf(".");
			else
				printf("%c", maze[y][x]);
		}
		printf("\n");	
	}
}

void	solve(char **maze, int width, int height)
{
	char	**seen;
	t_point	start = find_start(maze, 'S', width, height);
	
	seen = (char **) malloc(sizeof(char *) * (height + 1));
	seen[height] = NULL;
	for (int i = 0; i < height; i++)
	{
		seen[i] = (char *) malloc(sizeof(char) * (width + 1));
		memset(seen[i], '0', width);
		seen[i][width] = '\0';
	}
	if (walk(maze, seen, start.x, start.y, width, height) == true)
	{
		maze[start.y][start.x] = 'S';
		print_solution(maze, seen, width, height);
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
		temp = 0;
		for (int j = 0; maze[i][j] && maze[i][j] != '\n'; j++)
			temp++;
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
	solve(maze, width, height);
	return (0);
}
