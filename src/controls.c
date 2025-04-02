/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:55:51 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/02 16:29:26 by mmaksimo         ###   ########.fr       */
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
	{
		game->plr_angle -= 2;
		if (game->plr_angle == 0)
			game->plr_angle = 360;
		printf("Player's angle of view: %i\n", game->plr_angle);
	}
	else if (keydata.key == MLX_KEY_RIGHT && key_pressed(keydata))
	{
		game->plr_angle = (game->plr_angle % 360) + 2;
		// if (game->plr_angle == 360)
		// 	game->plr_angle = 0;
		printf("Player's angle of view: %i\n", game->plr_angle);
	}
	
// =======
// 		game->plr_angle -= 2;
// 	if (keydata.key == MLX_KEY_RIGHT && key_pressed(keydata))
// 		game->plr_angle += 2;
}

int	test_new_position(t_game *game, mlx_key_data_t keydata)
{
	t_ray test_position;

	test_position.ray_x = game->plr_pos_x;
	test_position.ray_y = game->plr_pos_y;
	if (keydata.key == MLX_KEY_W && key_pressed(keydata))
	{
		test_position.ray_x += cos(deg_to_rad(game->plr_angle)) / (PREC / 100);
		test_position.ray_y += sin(deg_to_rad(game->plr_angle)) / (PREC / 100);
	}
	else if (keydata.key == MLX_KEY_S && key_pressed(keydata))
	{
		test_position.ray_x -= cos(deg_to_rad(game->plr_angle)) / (PREC / 100);
		test_position.ray_y -= sin(deg_to_rad(game->plr_angle)) / (PREC / 100);
	}
	else if (keydata.key == MLX_KEY_A && key_pressed(keydata))
	{
		test_position.ray_x += cos(deg_to_rad(game->plr_angle - 90)) / (PREC / 100);
		test_position.ray_y += sin(deg_to_rad(game->plr_angle - 90)) / (PREC / 100);
	}
	else if (keydata.key == MLX_KEY_D && key_pressed(keydata))
	{
		test_position.ray_x += cos(deg_to_rad(game->plr_angle + 90)) / (PREC / 100);
		test_position.ray_y += sin(deg_to_rad(game->plr_angle + 90)) / (PREC / 100);
	}
	if (hit_the_wall(test_position, game))
		return(1);
	return(0);
	
}

static void	move_controls(t_game *game, mlx_key_data_t keydata)
{
	if (test_new_position(game, keydata) == 0)
	{
		if (keydata.key == MLX_KEY_W && key_pressed(keydata) && test_new_position(game, keydata) == 0)
		{
			game->plr_pos_x += cos(deg_to_rad(game->plr_angle)) / (PREC / 100);
			game->plr_pos_y += sin(deg_to_rad(game->plr_angle)) / (PREC / 100);
			printf("Player's position. X: %i\nY: %i\n", (int)game->plr_pos_x, (int)game->plr_pos_y);
		}
		else if (keydata.key == MLX_KEY_S && key_pressed(keydata) && test_new_position(game, keydata) == 0)
		{
			game->plr_pos_x -= cos(deg_to_rad(game->plr_angle)) / (PREC / 100);
			game->plr_pos_y -= sin(deg_to_rad(game->plr_angle)) / (PREC / 100);
			printf("Player's position. X: %i\nY: %i\n", (int)game->plr_pos_x, (int)game->plr_pos_y);
		}
		else if (keydata.key == MLX_KEY_A && key_pressed(keydata) && test_new_position(game, keydata) == 0)
		{
			game->plr_pos_x += cos(deg_to_rad(game->plr_angle - 90)) / (PREC / 100);
			game->plr_pos_y += sin(deg_to_rad(game->plr_angle - 90)) / (PREC / 100);
			printf("Player's position. X: %i\nY: %i\n", (int)game->plr_pos_x, (int)game->plr_pos_y);
		}
		else if (keydata.key == MLX_KEY_D && key_pressed(keydata) && test_new_position(game, keydata) == 0)
		{
			game->plr_pos_x += cos(deg_to_rad(game->plr_angle + 90)) / (PREC / 100);
			game->plr_pos_y += sin(deg_to_rad(game->plr_angle + 90)) / (PREC / 100);
			printf("Player's position. X: %i\nY: %i\n", (int)game->plr_pos_x, (int)game->plr_pos_y);
		}
	}
	else
		printf("There's a wall here!\n");		
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
