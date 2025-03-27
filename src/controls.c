/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:55:51 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/26 19:58:17 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	key_pressed(mlx_key_data_t keydata)
{
	if ((keydata.action == MLX_PRESS) || (keydata.action == MLX_REPEAT))
		return (true);
	return (false);
}

static void	turn_controls(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT && key_pressed(keydata))
		game->plr_angle -= 1;
	if (keydata.key == MLX_KEY_RIGHT && key_pressed(keydata))
		game->plr_angle += 1;
}

static void	move_controls(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W && key_pressed(keydata))
	{
		game->plr_pos_x += cos(deg_to_rad(game->plr_angle)) / (PREC / 100);
		game->plr_pos_y += sin(deg_to_rad(game->plr_angle)) / (PREC / 100);
	}
	if (keydata.key == MLX_KEY_S && key_pressed(keydata))
	{
		game->plr_pos_x -= cos(deg_to_rad(game->plr_angle)) / (PREC / 100);
		game->plr_pos_y -= sin(deg_to_rad(game->plr_angle)) / (PREC / 100);
	}
	if (keydata.key == MLX_KEY_A && key_pressed(keydata))
	{
		game->plr_pos_x += cos(deg_to_rad(game->plr_angle - 90)) / (PREC / 100);
		game->plr_pos_y += sin(deg_to_rad(game->plr_angle - 90)) / (PREC / 100);
	}
	if (keydata.key == MLX_KEY_D && key_pressed(keydata))
	{
		game->plr_pos_x += cos(deg_to_rad(game->plr_angle + 90)) / (PREC / 100);
		game->plr_pos_y += sin(deg_to_rad(game->plr_angle + 90)) / (PREC / 100);
	}
}

void	all_keyhooks(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	turn_controls(game, keydata);
	move_controls(game, keydata);
	if (keydata.key == MLX_KEY_ESCAPE && key_pressed(keydata))
		mlx_close_window(game->mlx);
}
