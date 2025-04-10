/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:42:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/10 17:11:56 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path(t_game *game, char *line, int fd)
{
	char	*path;
	int		fd_test;
	
	path = line + 2;
	while (ft_isspace(*path))
		path++;
	if (!ft_strendswith(path, ".xpm") && !ft_strendswith(path, ".png"))
		error_exit(game, line, fd, 1);
	fd_test = open(path, O_RDONLY);
	if (fd_test < 0)
	{
		close(fd_test);
		error_exit(game, line, fd, 8);
	}
	close(fd_test);
	return (path);
}

void	validate_color_format(char *rgb_seq, t_game *game, char *line, int fd)
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
				error_exit(game, line, fd, 2);

		if (rgb_seq[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
		error_exit(game, line, fd, 2);
}

t_rgba	parse_color(char *rgb_seq, t_game *game, char *line, int fd)
{
	t_rgba	rgba;
	int		sub_len;
	int		sub_count;
	int		color_value;
	char	*sub_seq;

	sub_len = 0;
	sub_count = -1;
	sub_seq = malloc(sizeof(char) * ft_strlen(rgb_seq));
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
			error_exit(game, line, fd, 7);
		}
		if (sub_count == 0)
			rgba.r = (uint32_t) color_value;
		else if (sub_count == 1)
			rgba.g = (uint32_t) color_value;
		else if (sub_count == 2)
			rgba.b = (uint32_t) color_value;
		rgb_seq++;
	}
	free(sub_seq);
	return (rgba);
}

uint32_t	get_color(t_game *game, char *line, int fd)
{
	t_rgba		color;
	uint32_t	out_color;
	char		*rgb_seq;

	rgb_seq = line + 1;
	while (ft_isspace(*rgb_seq))
		rgb_seq++;
	validate_color_format(rgb_seq, game, line, fd);
	color = parse_color(rgb_seq, game, line, fd);
	out_color = (color.r << 24) | (color.g << 16) | (color.b << 8) | 0xFF;
	return (out_color);
}

void	parse_map(void)
{}


void	process_tex_path(int dir, int *depth, int *unique, t_game *game, char *line, int fd)
{
	game->texture_path_nsew[dir] = ft_strdup(get_path(game, line, fd));
	if (!game->texture_path_nsew[dir])
		error_exit(game, line, fd, 0);
	*depth += 1;
	*unique += 1;
}

int	is_space_or_out(t_game *game, int i, int j)
{
	if (i < 0 || i >= game->map_height)
		return (1);
	if (j < 0 || j >= (int)ft_strlen(game->map[i]))
		return (1);
	if (game->map[i][j] == ' ')
		return (1);
	return (0);
}

void	check_open_walls(t_game *game)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	while (i < game->map_height)
	{		
		j = 0;
		line_len = (int) ft_strlen(game->map[i]);
		if (game->map[i][j] == '0' || game->map[i][line_len - 1] == '0')
			error_exit(game, NULL, -1, 3);
		while (j < line_len)
		{
			if ((i == 0 || i == game->map_height - 1
				|| is_space_or_out(game, i, j + 1)
				|| is_space_or_out(game, i, j - 1)
				|| is_space_or_out(game, i + 1, j)
				|| is_space_or_out(game, i - 1, j)
				|| is_space_or_out(game, i - 1, j - 1)
				|| is_space_or_out(game, i + 1, j - 1)
				|| is_space_or_out(game, i - 1, j + 1)
				|| is_space_or_out(game, i + 1, j + 1))
				&& ft_strchr("0NSEW", game->map[i][j]))
			{
				error_exit(game, NULL, -1, 3);
			}
			j++;
		}
		i++;
	}
}

int	read_map(int argc, char *filepath, t_game *game)
{
	int		fd;
	char	*line;
	int		unique = 0;
	int		height = 0;
	int		depth = 0;

	fd = check_args_get_fd(argc, filepath);
	if (fd < 0)
		return (-1);
	game = game;
	fd = fd;
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
		line = line;

		if (!ft_strchr("NSWEFC10", line[0]))
			error_exit(game, line, fd, 6);
		
		// For Texture Paths

		if (ft_strncmp(line, "NO", 2) == 0)
			process_tex_path(0, &depth, &unique, game, line, fd);
		else if (ft_strncmp(line, "SO", 2) == 0)
			process_tex_path(1, &depth, &unique, game, line, fd);
		else if (ft_strncmp(line, "EA", 2) == 0)
			process_tex_path(2, &depth, &unique, game, line, fd);
		else if (ft_strncmp(line, "WE", 2) == 0)
			process_tex_path(3, &depth, &unique, game, line, fd);

		// For Floor and Ceiling
		if (ft_strncmp(line, "F", 1) == 0)
		{
			game->floor_color = get_color(game, line, fd);
			depth++;
			unique++;
		}
		else if (ft_strncmp(line, "C", 1) == 0)
		{
			game->ceil_color = get_color(game, line, fd);
			depth++;
			unique++;
		}
		
		// For Map  (maybe put checks in map parsing?)
		if (ft_strncmp(line, "0", 1) == 0 && unique == 6)
				error_exit(game, line, fd, 3);

		else if (ft_strncmp(line, "1", 1) == 0 && unique == 6)
		{
			if (ft_strendswith(line, "0"))
				error_exit(game, line, fd, 3);
			depth++;
			height++;
		}
		free(line);	
	}
	if (height)
		unique++;
		
	// check there were 7 unique arguments
	if (unique != 7)
		error_exit(game, line, fd, 4);

	game->map_height = height;
	close(fd);

	// now we have height, we can allocate map rows
	game->map = malloc(sizeof(char *) * game->map_height + 1);

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nCould not open file");
		return (-1);
	}
	fd = fd;
	

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

		line = line;
		if (row > (depth - game->map_height))
		{
			int j = 0;
			while (line[j])
			{
				if (!ft_strchr(" NSWE10", line[j]))
					error_exit(game, line, fd, 5);
				j++;
			}
			if (line[j - 1] == ' ')
				while (!ft_isdigit(line[--j]))
					line[j] = '\0';
			if (max_width <= j)
				max_width = j;		
			game->map[i] = ft_strdup(line);
			if (!game->map[i])
				error_exit(game, line, fd, 0);
			i++;
		}
		row++;
		free(line);
		line = NULL;

	}
	game->map[i] = NULL;
	game->map_width = max_width;
	close(fd);

	check_open_walls(game);

	return (0);
}

