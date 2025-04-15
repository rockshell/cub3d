/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:49:05 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/10 23:18:11 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_row(t_game *game, char *line, int fd, int i)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (!ft_strchr(" \tNSWE10", line[j]))
			error_exit(game, line, fd, 5);
		j++;
	}
	if (j >= 1 && line[j - 1] == ' ')
		while (!ft_isdigit(line[--j]))
			line[j] = '\0';
	game->map[i] = ft_strdup(line);
	if (!game->map[i])
		error_exit(game, line, fd, 0);
}

void	get_map(t_game *game, int fd, int depth)
{
	int		i;
	int		row;
	int		map_ends;
	char	*line;

	i = 0;
	row = 1;
	map_ends = game->map_height + depth;
	line = get_next_line(fd);
	while (line)
	{
		if (row > depth && row <= map_ends)
		{
			line = trim_whitespaces(line, "\n\r");
			get_map_row(game, line, fd, i);
			i++;
		}
		row++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
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

bool	is_open_around(t_game *game, int i, int j)
{
	if ((i == 0
			|| i == game->map_height - 1
			|| is_space_or_out(game, i, j + 1)
			|| is_space_or_out(game, i, j - 1)
			|| is_space_or_out(game, i + 1, j)
			|| is_space_or_out(game, i - 1, j)
			|| is_space_or_out(game, i - 1, j - 1)
			|| is_space_or_out(game, i + 1, j - 1)
			|| is_space_or_out(game, i - 1, j + 1)
			|| is_space_or_out(game, i + 1, j + 1))
		&& ft_strchr("0NSEW", game->map[i][j]))
		return (true);
	return (false);
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
			if (is_open_around(game, i, j))
			{
				error_exit(game, NULL, -1, 3);
			}
			j++;
		}
		i++;
	}
}
