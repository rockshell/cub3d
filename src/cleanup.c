/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:50:22 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/15 22:52:28 by mmaksimo         ###   ########.fr       */
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
		free(game->tex_path_nsew[i]);
		game->tex_path_nsew[i] = NULL;
		i++;
	}
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
