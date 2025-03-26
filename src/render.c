/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:01:08 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/26 20:02:41 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_bg(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			if (i < WIN_HEIGHT / 2)
				mlx_put_pixel(game->img, j, i, game->ceil_color);
			else
				mlx_put_pixel(game->img, j, i, game->floor_color);
			j++;
		}
		i++;
	}
}

void	draw_wall(double distance, int width, t_game *game)
{
	int	i;
	int	height;

	i = HALF_HEIGHT;
	height = floor(HALF_HEIGHT / distance);
	while (i > HALF_HEIGHT - (height / 2))
	{
		mlx_put_pixel(game->img, width, i, 0x000000);
		i--;
	}
	i = HALF_HEIGHT;
	while (i < HALF_HEIGHT + (height / 2))
	{
		mlx_put_pixel(game->img, width, i, 0x000000);
		i++;
	}
}

void	render_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_bg((t_game *)game);
	ray_casting(game);
	mlx_key_hook(game->mlx, all_keyhooks, game);
}
