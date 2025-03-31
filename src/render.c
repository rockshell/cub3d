/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:01:08 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/01 00:01:01 by mmaksimo         ###   ########.fr       */
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

void	draw_wall(double distance, int screen_width, t_game *game)
{
	int	y;
	int	screen_height;

	int index = 0;
	uint32_t red = 0x00;
	uint32_t green = 0x00;
	uint32_t blue = 0x00;
	uint32_t alpha = 0x00;
	uint32_t color;

	int height = game->assets->n_image->height;
	int width = game->assets->n_image->width;


	y = HALF_HEIGHT;
	screen_height = floor(HALF_HEIGHT / distance);

	while (y > HALF_HEIGHT - (screen_height / 2))
	{
		// mlx_image_to_window(game->mlx, game->assets->n_image, width, i);
		index = ((y % height) * width + screen_width) * 4;
		red = game->assets->n_image->pixels[index] << 24;
		green = game->assets->n_image->pixels[index + 1] << 16;
		blue = game->assets->n_image->pixels[index + 2] << 8;
		alpha = game->assets->n_image->pixels[index + 3];
		color = red | green | blue | alpha;
		mlx_put_pixel(game->img, screen_width, y, color);

			// mlx_put_pixel(game->img, x, y, color);
		y -= 1;
	}
	y = HALF_HEIGHT;
	while (y < HALF_HEIGHT + (screen_height / 2))
	{
		// mlx_put_pixel(game->img, screen_width, i, game->assets->e_image->pixels[i]);
		// mlx_image_to_window(game->mlx, game->assets->n_image, width, i);
		index = ((y % height) * width + screen_width) * 4;
		red = game->assets->n_image->pixels[index] << 24;
		green = game->assets->n_image->pixels[index + 1] << 16;
		blue = game->assets->n_image->pixels[index + 2] << 8;
		alpha = game->assets->n_image->pixels[index + 3];
		color = red | green | blue | alpha;
		mlx_put_pixel(game->img, screen_width, y, color);
		y += 1;
	}


	
	// for (int y = 0; y < height; y++)
	// {
	// 	for (int x = 0; x < width; x++)
	// 	{
	// 		// if ((i - x - 1) % 3 == 0)
	// 		// 	alpha = (game->assets->n_image->pixels[i]);
	// 		// printf("PIXEL DATA: %x\n", alpha);

	// 	}

	// }
}

void	render_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_bg((t_game *)game);
	ray_casting(game);
	mlx_key_hook(game->mlx, all_keyhooks, game);
}
