/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:42:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/11 19:34:16 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	cube_atoi(const char *nptr)
{
	long int		num;
	unsigned int	i;

	num = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		return (-1);
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		num = (num + (nptr[i] - 48)) * 10;
		if (num > INT_MAX)
			return (-1);
		i++;
	}
	num /= 10;
	if (nptr[i] != '\0' || num > 255)
		return (-1);
	return ((int) num);
}

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
		if (*line == '\n')
		{
			free(line);
			continue ;
		}

		// For sides		
		char *tmp_line = line;
		line = ft_strtrim(tmp_line, " \t\n");
		free(tmp_line);
		tmp_line = NULL;
		// Maybe save trimmed map to global struct like mvenmo does?

		/* CHECK ALL FIRST CHAR AFTER TRIMMING IS SWNEFC01 
		 - THAT WOULD MEAN HAVE MORE OR LESS REQUIRED FORMAT*/

		if (!ft_strchr("NSWEFC01", line[0])) // && and no more than 6 unique chars!
		{
			printf("Error\nInvalid map format\n");
			free_exit(line, game, fd);
		}

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

		// For Floor and Ceiling
		if (ft_strncmp(line, "F", 1) == 0)
			game->floor_color = get_color(line, game, fd);
		else if (ft_strncmp(line, "C", 1) == 0)
			game->ceil_color = get_color(line, game, fd);
		
		// For 01s
		
		
		free(line);
		
	}
	
	// for (int i = 0; i < 4; i++)
	// 	printf("%s\n",game->tex_path_nsew[i]);

	close(fd);

	return (0);
}
