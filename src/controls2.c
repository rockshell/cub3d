/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:55:51 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/10 23:07:08 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	k_hold(mlx_key_data_t keydata)
{
	if ((keydata.action == MLX_PRESS) || (keydata.action == MLX_REPEAT))
		return (true);
	return (false);
}

void	move_ray(double *ray_x, double *ray_y, enum keys key, t_game *game)
{
	if (key == 87)
	{
		*ray_x += cos(deg_to_rad(game->plr_angle)) / (PREC / 100);
		*ray_y += sin(deg_to_rad(game->plr_angle)) / (PREC / 100);
	}
	else if (key == 83)
	{
		*ray_x -= cos(deg_to_rad(game->plr_angle)) / (PREC / 100);
		*ray_y -= sin(deg_to_rad(game->plr_angle)) / (PREC / 100);
	}
	else if (key == 65)
	{
		*ray_x += cos(deg_to_rad(game->plr_angle - 90)) / (PREC / 100);
		*ray_y += sin(deg_to_rad(game->plr_angle - 90)) / (PREC / 100);
	}
	else if (key == 68)
	{
		*ray_x += cos(deg_to_rad(game->plr_angle + 90)) / (PREC / 100);
		*ray_y += sin(deg_to_rad(game->plr_angle + 90)) / (PREC / 100);
	}
}
