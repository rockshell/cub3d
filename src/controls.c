/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:55:51 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/11 16:57:22 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	turn_controls(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT && k_hold(keydata))
	{
		game->plr_angle -= TURN_RATIO;
		if (game->plr_angle == -TURN_RATIO)
			game->plr_angle = 360 - TURN_RATIO;
	}
	else if (keydata.key == MLX_KEY_RIGHT && k_hold(keydata))
		game->plr_angle = (game->plr_angle % 360) + TURN_RATIO;
}

int	t_pos(t_game *game, mlx_key_data_t keydata)
{
	t_ray	test_pos;

	test_pos.ray_x = game->plr_pos_x;
	test_pos.ray_y = game->plr_pos_y;
	if (keydata.key == MLX_KEY_W && k_hold(keydata))
		move_ray(&test_pos.ray_x, &test_pos.ray_y, MLX_KEY_W, game);
	else if (keydata.key == MLX_KEY_S && k_hold(keydata))
		move_ray(&test_pos.ray_x, &test_pos.ray_y, MLX_KEY_S, game);
	else if (keydata.key == MLX_KEY_A && k_hold(keydata))
		move_ray(&test_pos.ray_x, &test_pos.ray_y, MLX_KEY_A, game);
	else if (keydata.key == MLX_KEY_D && k_hold(keydata))
		move_ray(&test_pos.ray_x, &test_pos.ray_y, MLX_KEY_D, game);
	if (hit_the_wall(test_pos, game))
		return (1);
	return (0);
}

static void	move_controls(t_game *g, mlx_key_data_t data)
{
	if (t_pos(g, data) == 0)
	{
		if (data.key == MLX_KEY_W && k_hold(data) && t_pos(g, data) == 0)
			move_ray(&g->plr_pos_x, &g->plr_pos_y, MLX_KEY_W, g);
		else if (data.key == MLX_KEY_S && k_hold(data) && t_pos(g, data) == 0)
			move_ray(&g->plr_pos_x, &g->plr_pos_y, MLX_KEY_S, g);
		else if (data.key == MLX_KEY_A && k_hold(data) && t_pos(g, data) == 0)
			move_ray(&g->plr_pos_x, &g->plr_pos_y, MLX_KEY_A, g);
		else if (data.key == MLX_KEY_D && k_hold(data) && t_pos(g, data) == 0)
			move_ray(&g->plr_pos_x, &g->plr_pos_y, MLX_KEY_D, g);
	}
}

void	key_hooks(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	turn_controls(game, keydata);
	move_controls(game, keydata);
	if (keydata.key == MLX_KEY_ESCAPE && k_hold(keydata))
		mlx_close_window(game->mlx);
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	int32_t	x;
	int32_t	y;
	t_game	*game;

	(void) ypos;
	game = (t_game *) param;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	game->cursr_last_x = x;
	game->cursr_last_y = y;
	if (xpos > (double) game->cursr_last_x)
	{
		game->plr_angle -= TURN_RATIO;
		if (game->plr_angle == -TURN_RATIO)
			game->plr_angle = 360 - TURN_RATIO;
	}
	else if (xpos < (double) game->cursr_last_x)
		game->plr_angle = (game->plr_angle % 360) + TURN_RATIO;
}
