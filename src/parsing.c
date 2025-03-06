/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:42:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/06 16:19:44 by mmaksimo         ###   ########.fr       */
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
	// MAYBE NOT THE BEST WAY HERE...
	// path[ft_strlen(path) - 1] = '\0';
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

t_rgb	get_color(char *line, t_game *game, int fd)
{
	t_rgb	color;
	char	*rgb_seq;

	/* Need checks for errors and exits */
	(void) game;
	(void) fd;
	
	rgb_seq = line + 1;
	while (ft_isspace(*rgb_seq))
		rgb_seq++;

	int sub_len = 0;
	int sub_count = 0;
	char *sub_seq;

	sub_seq = rgb_seq;
	while (*rgb_seq)
	{
		
		if (*rgb_seq == ',')
		{
			if (sub_count > 2)
			{
				printf("Error\nToo many colors in sequence");
				free_exit(line, game, fd);
			}
			sub_seq[sub_len] = '\0';
			sub_len = 0;

			/* Check atoi output */
			if (sub_count == 0)
				color.r = ft_atoi(sub_seq);
			else if (sub_count == 1)
				color.g = ft_atoi(sub_seq);
			else if (sub_count == 2)
				color.b = ft_atoi(sub_seq);  // FIX BLUE! 
				
			sub_seq = rgb_seq + 1;
			sub_count++;
		}
		sub_len++;
		rgb_seq++;
	}
	if (sub_count == 2)
		color.b = ft_atoi(sub_seq);  // FIX BLUE! 
	
	

	printf("Red Color: %u\n", color.r);
	printf("Green Color: %u\n", color.g);
	printf("Blue Color: %u\n", color.b);
	return (color);
	 
}


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
	
	char	*line; 
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
			
		/*
		◦ Except for the map content, each type of element can be separated by one or
		more empty line(s).

		◦ Except for the map content which always has to be the last, each type of
		element can be set in any order in the file.

		◦ Except for the map, each type of information from an element can be separated
		by one or more space(s).

		*/
		if (*line == '\n')
		{
			free(line);
			continue ;
		}


		// For sides
		
		char *tmp_line = line;
		line = ft_strtrim(tmp_line, " \t\n");
		free(tmp_line);

		if (ft_isdigit(*line))
		{
			free(line);
			break ;
		}
		
		if (ft_strncmp(line, "NO", 2) == 0)
			game->tex_path_nsew[0] = ft_strdup(get_path(line, game, fd));
		else if (ft_strncmp(line, "SO", 2) == 0)
			game->tex_path_nsew[1] = ft_strdup(get_path(line, game, fd));
		else if (ft_strncmp(line, "EA", 2) == 0)
			game->tex_path_nsew[2] = ft_strdup(get_path(line, game, fd));
		else if (ft_strncmp(line, "WE", 2) == 0)
			game->tex_path_nsew[3] = ft_strdup(get_path(line, game, fd));
		// else
		// {
		// 		printf("Error\nInvalid map element");
		// 		free_exit(line, game, fd);
		// }
			
		// printf("%s", line);


		// For Floor and Ceiling

		if (ft_strncmp(line, "F", 1) == 0)
			game->floor_color = get_color(line, game, fd);
		else if (ft_strncmp(line, "C", 1) == 0)
			game->ceil_color = get_color(line, game, fd);
		
		
		free(line);
		
	}
	
	for (int i = 0; i < 4; i++)
		printf("%s\n",game->tex_path_nsew[i]);

	close(fd);

	return (0);
}
