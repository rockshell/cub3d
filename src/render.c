/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:01:08 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/02 14:02:45 by mmaksimo         ###   ########.fr       */
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

void	draw_wall(double distance, int x, t_game *game)
{
	int		y;
	double	wall_height;

	int index = 0;
	uint32_t red = 0x00;
	uint32_t green = 0x00;
	uint32_t blue = 0x00;
	uint32_t alpha = 0x00;
	uint32_t color;

	int height = game->assets->s_image->height;
	int width = game->assets->s_image->width;
	double k_depth = 1.0 / (1.0 + distance * 0.05);
	
	wall_height = floor(HALF_HEIGHT / distance);
	y = HALF_HEIGHT - (wall_height / 2);

	while (y < HALF_HEIGHT + (wall_height / 2))
	{
		index = ((y % height) * width + (x % width)) * 4 ;
		red = ((uint8_t)(game->assets->s_image->pixels[index] * k_depth)) << 24;
		green = ((uint8_t)(game->assets->s_image->pixels[index + 1] * k_depth))<< 16;
		blue = ((uint8_t)(game->assets->s_image->pixels[index + 2] * k_depth)) << 8;
		alpha = game->assets->s_image->pixels[index + 3];
		color = red | green | blue | alpha;
		mlx_put_pixel(game->img, x, y, color);
		y++;
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
