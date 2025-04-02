/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arch <arch@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:06 by arch              #+#    #+#             */
/*   Updated: 2025/04/01 21:03:01 by arch             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_struct(t_game *game)
{
	int	i;

	game->texture_path_nsew = malloc(sizeof(char *) * 4);
	if (!game->texture_path_nsew)
		return (-1);
	i = 0;
	while (i < 4)
	{
		game->texture_path_nsew[i] = NULL;
		i++;
	}
	game->ceil_color = 0;
	game->floor_color = 0;
	game->plr_pos_x = 0.0;
	game->plr_pos_y = 0.0;
	game->map = NULL;
	game->prev_frame = NULL;
	game->walls_arr = malloc(sizeof(double) * WIN_WIDTH);
	return (0);
}