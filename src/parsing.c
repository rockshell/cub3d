/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arch <arch@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:42:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/21 18:49:52 by arch             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


char *get_path(t_error error_s)
{
	char	*path;
	int		fd_test;
	
	path = error_s.line + 2;
	// both absolute and relative are valid?
	while (ft_isspace(*path))
		path++;
	if (!ft_strendswith(path, ".xpm") && !ft_strendswith(path, ".png"))
		error_exit(error_s, 1);
		
	// Check the existence of file
	fd_test = open(path, O_RDONLY);
	if (fd_test < 0)
	{
		close(fd_test);
		error_exit(error_s, 8);
	}
	close(fd_test);
	return (path);
}

void	validate_color_format(char *rgb_seq, t_error error_s)
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
				error_exit(error_s, 2);

		if (rgb_seq[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
		error_exit(error_s, 2);
}

t_rgb	parse_color(char *rgb_seq, t_error error_s)
{
	t_rgb	color;
	int		sub_len;
	int		sub_count;
	int		color_value;
	char	*sub_seq;

	sub_len = 0;
	sub_count = -1;
	sub_seq = malloc(sizeof(char) * ft_strlen(rgb_seq));
	// printf("RBSEQ: %s\n", rgb_seq);
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
			free(sub_seq);
			error_exit(error_s, 7);
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

uint32_t	get_color(t_error error_s)
{
	t_rgb		color;
	uint32_t	out_color;
	char		*rgb_seq;

	rgb_seq = error_s.line + 1;
	while (ft_isspace(*rgb_seq))
		rgb_seq++;
	validate_color_format(rgb_seq, error_s);
	color = parse_color(rgb_seq, error_s);
	out_color = (color.r << 24) | (color.g << 16) | (color.b << 8) | 0xFF;


	return (out_color);
}

void	parse_map(void)
{}


void	process_tex_path(int dir, int *depth, int *unique, t_error error_s)
{
	error_s.game->texture_path_nsew[dir] = ft_strdup(get_path(error_s));
	if (!error_s.game->texture_path_nsew[dir])
		error_exit(error_s, 0);
	*depth += 1;
	*unique += 1;
}

int	read_map(int argc, char *filepath, t_game *game)
{
	// First check trimmed map and get elements data

	t_error	error_s;

	int		fd; 
	char	*line; 
	int		unique = 0;
	int		height = 0;
	int		depth = 0;

	fd = check_args_get_fd(argc, filepath);
	if (fd < 0)
		return (-1);

	error_s.game = game;
	error_s.fd = fd;

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
		
		if (*line == '\0')
		{
			depth++;
			free(line);
			continue ;
		}
		// put line in error set
		error_s.line = line;

		if (!ft_strchr("NSWEFC10", line[0]))
			error_exit(error_s, 6);
		
		// For Texture Paths

		if (ft_strncmp(line, "NO", 2) == 0)
			process_tex_path(0, &depth, &unique, error_s);
		else if (ft_strncmp(line, "SO", 2) == 0)
			process_tex_path(1, &depth, &unique, error_s);
		else if (ft_strncmp(line, "EA", 2) == 0)
			process_tex_path(2, &depth, &unique, error_s);
		else if (ft_strncmp(line, "WE", 2) == 0)
			process_tex_path(3, &depth, &unique, error_s);

		// For Floor and Ceiling
		if (ft_strncmp(line, "F", 1) == 0)
		{
			game->floor_color = get_color(error_s);
			depth++;
			unique++;
		}
		else if (ft_strncmp(line, "C", 1) == 0)
		{
			game->ceil_color = get_color(error_s);
			depth++;
			unique++;
		}
		
		// For Map  (maybe put checks in map parsing?)
		if (ft_strncmp(line, "0", 1) == 0 && unique == 6)
				error_exit(error_s, 3);

		else if (ft_strncmp(line, "1", 1) == 0 && unique == 6)
		{
			if (ft_strendswith(line, "0"))
				error_exit(error_s, 3);
			depth++;
			height++;
		}
		free(line);	
	}
	if (height)
		unique++;
		
	// check there were 7 unique arguments
	if (unique != 7)
		error_exit(error_s, 4);

	game->map_height = height;
	close(fd);

	// now we have height, we can allocate map rows
	game->map = malloc(sizeof(char *) * height + 1);

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nCould not open file");
		return (-1);
	}
	error_s.fd = fd;
	

	// Get map
	int row = 1;
	int max_width = 0;
	int i = 0;
	char *tmp_line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
			
		// trim fun
		tmp_line = line;
		line = ft_strtrim(tmp_line, "\n\r");
		free(tmp_line);
		tmp_line = NULL;

		error_s.line = line;
		if (row > (depth - height))
		{
			int j = 0;
			while (line[j])
			{
				if (!ft_strchr(" NSWE10", line[j]))
					error_exit(error_s, 5);
				j++;
			}
			if (line[j - 1] == ' ')
				while (!ft_isdigit(line[--j]))
					line[j] = '\0';
			if (max_width <= j)
				max_width = j;		
			game->map[i] = ft_strdup(line);
			if (!game->map[i])
				error_exit(error_s, 0);
			i++;
		}
		row++;
		free(line);
		line = NULL;

	}
	game->map[i] = NULL;
	game->map_width = max_width;
	close(fd);

	// printf("map width:	%d\n", game->map_width);
	// printf("map height:	%d\n", game->map_height);



	// Check for player and get position
	
	// Check for borders 
	int	j;
	int	line_len;
	i = 0;
	while (i < game->map_height)
	{		
		j = 0;
		line_len = (int) ft_strlen(game->map[i]);
		if (game->map[i][j] == '0' || game->map[i][line_len - 1] == '0')
		{
			printf("Error\nInvalid map format: open wall\n");
			printf("row: %d\ncol: %d\n", i + 1, j + 1);
			free_game(game);
			exit(1);
		}
		while (j < line_len)
		{
			// printf("%c", game->map[i][j]);
			if ((i == 0 || i == game->map_height - 1 || (game->map[i][j + 1] == ' ')
				|| (game->map[i][j - 1] == ' ') || (game->map[i + 1][j] == ' ')
				|| (game->map[i + 1][j] == '\0') || (game->map[i - 1][j] == '\0')
				|| (game->map[i - 1][j] == ' ')) && ft_strchr("0NSEW", game->map[i][j]))
			{
				// work on error_exit function
				printf("Error\nInvalid map format: open wall\n");
				printf("row: %d\ncol: %d\n", i + 1, j + 1);
				free_game(game);
				exit(1);

			}
			j++;
		}
		// printf("\n");
		i++;
	}

	// for (int i = 0; i < game->map_height; i++)
	// 	printf("%s\n",game->map[i]);

	// printf("-- %s\n",game->map[9]);


	return (0);
}

