/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:42:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/13 01:39:59 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


char *get_path(char *line, t_game *game, int fd)
{
	char	*path;
	int		fd_test;
	
	path = line + 2;
	// both absolute and relative are valid?
	while (ft_isspace(*path))
		path++;
	if (!ft_strendswith(path, ".xpm"))
	{
		printf("Error\nInvalid texture format");
		free_exit(line, game, fd);
	}
	// Check the existence of file
	fd_test = open(path, O_RDONLY);
	if (fd_test < 0)
	{
		printf("Error\nInvalid file path");
		close(fd_test);
		free_exit(line, game, fd);
	}
	close(fd_test);
	return (path);
}

void	validate_color_format(char *rgb_seq, char *line, t_game *game, int fd)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (rgb_seq[i])
	{
		if ((!ft_isdigit(rgb_seq[i]) && rgb_seq[i] != ',') || rgb_seq[0] == ','
			|| (rgb_seq[i] == ',' && !rgb_seq[i + 1])
			|| (rgb_seq[i] == ',' && rgb_seq[i + 1] == ','))
		{
			printf("Error\nInvalid map format\n");
			free_exit(line, game, fd);
		}
		if (rgb_seq[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
	{
		printf("Error\nInvalid map format\n");
		free_exit(line, game, fd);
	}	
}

t_rgb	parse_color(char *rgb_seq, char *line, t_game *game, int fd)
{
	t_rgb	color;
	int		sub_len;
	int		sub_count;
	int		color_value;
	char	*sub_seq;

	sub_len = 0;
	sub_count = -1;
	sub_seq = malloc(sizeof(char) * 4);
	while (*rgb_seq)
	{
		while (ft_isdigit(*rgb_seq))
		{
			sub_seq[sub_len] = *rgb_seq;
			sub_len++;
			rgb_seq++;
		}
		sub_count++;
		sub_seq[sub_len] = '\0';
		sub_len = 0;
		color_value = cube_atoi(sub_seq);
		if (color_value < 0)
		{
			printf("Error\nInvalid color value\n");
			free(sub_seq);
			free_exit(line, game, fd);
		}
		if (sub_count == 0)
			color.r = color_value;
		else if (sub_count == 1)
			color.g = color_value;
		else if (sub_count == 2)
			color.b = color_value;
		rgb_seq++;
	}
	free(sub_seq);
	return (color);
}

t_rgb	get_color(char *line, t_game *game, int fd)
{
	t_rgb	color;
	char	*rgb_seq;

	rgb_seq = line + 1;
	while (ft_isspace(*rgb_seq))
		rgb_seq++;
	validate_color_format(rgb_seq, line, game, fd);
	color = parse_color(rgb_seq, line, game, fd);

	// printf("Red Color: %u\n", color.r);
	// printf("Green Color: %u\n", color.g);
	// printf("Blue Color: %u\n", color.b);
	return (color);
}

void	parse_map(void)
{}
		
int	get_map(int argc, char *filepath, t_game *game)
{
	// Check argument count (exactly 2 arguments: executable and map file)
	if (argc != 2)
	{
		errno = EINVAL;
		perror("Error\nProgram accepts only 1 argument");
		return (-1);
	}
	
	// Validate map file extension (.cub)
	if (ft_strendswith(filepath, ".cub") == 0)
	{
		errno = EINVAL;
		perror("Error\nFile must be of type '.cub'");
		return (-1);
	}

	// Parse and validate map file
	
	int fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		errno = EBADF;
		perror("Error\nCould not open file");
		return (-1);
	}


	// First check trimmed map and get elements data
	
	char	*line; 
	int		unique = 0;
	int		height = 0;
	int		depth = 0;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;

		// Trim whitespaces
		char *tmp_line = line;
		line = ft_strtrim(tmp_line, " \t\n\r");
		free(tmp_line);
		tmp_line = NULL;
		// Maybe save trimmed map to global struct like mvenmo does?
		
		if (*line == '\0')
		{
			depth++;
			free(line);
			continue ;
		}
		
		if (!ft_strchr("NSWEFC10", line[0]))
		{
			printf("Error\nInvalid map format\n");
			free_exit(line, game, fd);
		}
		
		// For Texture Paths
		if (ft_strncmp(line, "NO", 2) == 0)
		{
			game->tex_path_nsew[0] = ft_strdup(get_path(line, game, fd));
			if (!game->tex_path_nsew[0])
			{
				printf("Error\nAllocation failed\n");
				free_exit(line, game, fd);
			}
			depth++;
			unique++;
		}
		else if (ft_strncmp(line, "SO", 2) == 0)
		{
			game->tex_path_nsew[1] = ft_strdup(get_path(line, game, fd));
			if (!game->tex_path_nsew[1])
			{
				printf("Error\nAllocation failed\n");
				free_exit(line, game, fd);
			}
			depth++;
			unique++;
		}
		else if (ft_strncmp(line, "EA", 2) == 0)
		{
			game->tex_path_nsew[2] = ft_strdup(get_path(line, game, fd));
			if (!game->tex_path_nsew[2])
			{
				printf("Error\nAllocation failed\n");
				free_exit(line, game, fd);
			}
			depth++;
			unique++;
		}
		else if (ft_strncmp(line, "WE", 2) == 0)
		{
			game->tex_path_nsew[3] = ft_strdup(get_path(line, game, fd));
			if (!game->tex_path_nsew[3])
			{
				printf("Error\nAllocation failed\n");
				free_exit(line, game, fd);
			}
			depth++;
			unique++;
		}

		// For Floor and Ceiling
		if (ft_strncmp(line, "F", 1) == 0)
		{
			game->floor_color = get_color(line, game, fd);
			depth++;
			unique++;
		}
		else if (ft_strncmp(line, "C", 1) == 0)
		{
			game->ceil_color = get_color(line, game, fd);
			depth++;
			unique++;
		}
		
		// For Map  (maybe put checks in map parsing?)
		if (ft_strncmp(line, "0", 1) == 0 && unique == 6)
		{
			printf("Error\nInvalid map format: open wall\n");
			free_exit(line, game, fd);
		}
		else if (ft_strncmp(line, "1", 1) == 0 && unique == 6)
		{
			if (ft_strendswith(line, "0"))
			{
				printf("Error\nInvalid map format: open wall\n");
				free_exit(line, game, fd);
			}
			depth++;
			height++;
		}
		free(line);	
	}
	if (height)
		unique++;
		
	// printf("height:	%d\n", height);
	// printf("unique:	%d\n", unique);
	// printf("depth:	%d\n", depth);

	// check there were 7 unique arguments
	if (unique != 7)
	{
		perror("Error\nInvalid map format\n");
		return (-1);
	}
	game->map_height = height;
	close(fd);

	// now we have height, we can allocate map rows
	game->map = malloc(sizeof(char *) * height + 1);

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		errno = EBADF;
		perror("Error\nCould not open file");
		return (-1);
	}

	
	int row = 1;
	int max_width = 0;
	int i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;

		// Trim trailing newline chars
		char *tmp_line = line;
		line = ft_strtrim(tmp_line, "\n\r");
		free(tmp_line);
		tmp_line = NULL;

		if (row > (depth - height))
		{
			// printf("%s", line);
			// checks
			int j = 0;
			while (line[j])
			{
				if (!ft_strchr(" NSWE10", line[j]))
				{
					printf("Error\nInvalid map format\n");
					free_exit(line, game, fd);
				}
				j++;
			}
			// what to do with trailing spaces if there are? 
			// get width
			int line_width = ft_strlen(line);
			// printf("\n%d\n", line_width);
			game->map[i] = ft_strdup(line);
			i++;
			if (max_width <= line_width)
				max_width = line_width;
		
		}
		
		row++;
		
		free(line);	
	}
	game->map[i] = NULL;
	game->map_width = max_width;


	// printf("map width:	%d\n", game->map_width);
	// printf("map height:	%d\n", game->map_height);

	
	for (int i = 0; i < game->map_height; i++)
		printf("%s\n",game->map[i]);

	close(fd);

	return (0);
}

// int	get_map_width()