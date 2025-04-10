/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:50:22 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/10 23:46:11 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
		{
			if (game->map[i])
			{
				free(game->map[i]);
				game->map[i] = NULL;
			}
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}

void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->tex_path[i])
		{
			free(game->tex_path[i]);
			game->tex_path[i] = NULL;
		}
		i++;
	}
	free(game->tex_path);
	game->tex_path = NULL;
	free_map(game);
	free(game->walls->side);
	free(game->walls->walls_arr);
	free(game->walls);
	free(game->tex_pos_x_arr);
	free(game);
}

void	free_exit(t_game *game, char *line, int fd)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	free_game(game);
	if (fd >= 0)
		close(fd);
	exit(EXIT_FAILURE);
}
