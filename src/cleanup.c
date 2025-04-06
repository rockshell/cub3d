/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:50:22 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/06 21:46:15 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->texture_path_nsew[i])
		{
			free(game->texture_path_nsew[i]);
			game->texture_path_nsew[i] = NULL;
		}
		i++;
	}
	free(game->texture_path_nsew);
	game->texture_path_nsew = NULL;
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
	if (game->assets)
		free(game->assets);
	free(game->walls->side);
	free(game->walls->walls_arr);
	free(game->walls);
	free(game->tex_pos_x_arr);
	free(game);
}

void	free_exit(t_error error_s)
{
	if (error_s.line)
	{
		free(error_s.line);
		error_s.line = NULL;
	}
	free_game(error_s.game);
	if (error_s.fd >= 0)
		close(error_s.fd);
	exit(EXIT_FAILURE);	
}
