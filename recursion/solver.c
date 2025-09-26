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

typedef struct s_mazeinfo
{
	int		start_x;
	int		start_y;
	int		height;
	int		width;
}		t_mazeinfo;

void	free_maze(char **maze, t_mazeinfo *data);
int		get_maze_width(char **maze);
int		get_maze_height(char *file);
void	print_solution(char **maze, char **seen, t_mazeinfo *data);
void	find_start(char **maze, char c, t_mazeinfo *data);

bool	can_walk(char **maze, char **seen, int x, int y, t_mazeinfo *data)
{
	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return (false);
	if (maze[y][x] == '1')
		return (false);
	if (seen[y][x] == true)
		return (false);
	return (true);
}

bool walk(char **maze, char **seen, int x, int y, t_mazeinfo *data)
{
	if (y < 0 || x < 0)
		return (false);
	if (maze[y] && maze[y][x] == 'E')
	{
		seen[y][x] = '1';
		return (true);
	}
	if (can_walk(maze, seen, x, y, data) == true)
	{
		seen[y][x] = '1';
		maze[y][x] = '1';
		if (walk(maze, seen, x, y + 1, data) == true)
			return (true);
		if (walk(maze, seen, x + 1, y, data) == true)
			return (true);
		if (walk(maze, seen, x, y - 1, data) == true)
			return (true);
		if (walk(maze, seen, x - 1, y, data) == true)
			return (true);
		seen[y][x] = '0';
		maze[y][x] = '0';
	}
	return (false);
}

void	solve(char **maze, t_mazeinfo *data)
{
	char	**seen;

	find_start(maze, 'S', data);
	if (data->start_x == -1 || data->start_y == -1)
	{
		printf("start not found!\n");
		return ;
	}
	seen = (char **) malloc(sizeof(char *) * (data->height + 1));
	seen[data->height] = NULL;
	for (int i = 0; i < data->height; i++)
	{
		seen[i] = (char *) malloc(sizeof(char) * (data->width + 1));
		memset(seen[i], '0', data->width);
		seen[i][data->width] = '\0';
	}
	if (walk(maze, seen, data->start_x, data->start_y, data) == true)
	{
		maze[data->start_y][data->start_x] = 'S';
		print_solution(maze, seen, data);
	}
	else
		printf("end not found!\n");
	free_maze(seen, data);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("please pick a map\n");
		printf("eg: ./a.out \"maze\"\n");
		return (0);
	}

	char **maze;

	t_mazeinfo *data;
	data = (t_mazeinfo *) malloc(sizeof(t_mazeinfo));

	data->height = get_maze_height(argv[1]);
	maze = (char **) malloc(sizeof(char *) * (data->height + 1));
	maze[data->height] = NULL;
	
	
	FILE *fd = fopen(argv[1], "r");
	char *line = NULL;
	size_t len = 0;
	int i = 0;
	while (getline(&line, &len, fd) != -1)
	{
		maze[i] = strdup(line);
		free(line);
		line = NULL;
		i++;
	}
	free(line);
	line = NULL;
	fclose(fd);
	data->width = get_maze_width(maze);
	
	solve(maze, data);
	free_maze(maze, data);
	free(data);
	return (0);
}

// HELPER FUNCTIONS

// calculates the "height" of the maze by counting the number of lines
int	get_maze_height(char *file)
{
	FILE *fd = fopen(file, "r");
	char *line = NULL;
	size_t len = 0;
	int	height = 0;

	while (getline(&line, &len, fd) != -1)
	{
		height++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	return (fclose(fd), height);
}

// calculates the "width", which is the largest width of the map
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

// prints the final output
// prints the maze, replacing 0 with space and the path with *
void	print_solution(char **maze, char **seen, t_mazeinfo *data)
{
	for (int y = 0; y < data->height && maze[y]; y++)
	{
		for (int x = 0; x < data->width && maze[y][x]; x++)
		{
			if (maze[y][x] == '1' && seen[y][x] == '1')
				printf("*");
			else if (maze[y][x] == '0' && seen[y][x] == '0')
				printf(" ");
			else
				printf("%c", maze[y][x]);
		}
		printf("\n");	
	}
}

// used to free the maze and seen arrays
void	free_maze(char **maze, t_mazeinfo *data)
{
	for (int i = 0; i < data->height && maze[i]; i++)
		free(maze[i]);
	free(maze);
}

// used to locate the start point which is the initial value for the recursive
// walk function
void	find_start(char **maze, char c, t_mazeinfo *data)
{
	data->start_x = -1;
	data->start_y = -1;
	for (int i = 0; i < data->height; i++)
		for (int j = 0; j < data->width; j++)
		{
			if (maze[i][j] == c)
			{
				data->start_x = j;
				data->start_y = i;
			}
		}
}
