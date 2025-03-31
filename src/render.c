/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arch <arch@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:01:08 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/31 20:59:04 by arch             ###   ########.fr       */
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
		mlx_put_pixel(game->img, width, i, game->assets->e_image->pixels[i]);
		// mlx_image_to_window(game->mlx, game->assets->n_image, width, i);
		i -= 1;
	}
	i = HALF_HEIGHT;
	while (i < HALF_HEIGHT + (height / 2))
	{
		mlx_put_pixel(game->img, width, i, game->assets->e_image->pixels[i]);
		// mlx_image_to_window(game->mlx, game->assets->n_image, width, i);
		i += 1;
	}
}

void	render_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_bg((t_game *)game);
	
    int i = 0;
	// uint8_t red = 0x00;
	// uint8_t green = 0x00;
	// uint8_t blue = 0x00;
	uint8_t alpha = 0x00;

	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			if ((i - x - 1) % 3 == 0)
				alpha = (game->assets->s_image->pixels[i]);
			printf("PIXEL DATA: %x\n", alpha);
			// uint32_t color = (game->assets->s_image->pixels[i] << 24) | 0xff;
			// mlx_put_pixel(game->img, x, y, color);
			i++;
		}

	}

	// ray_casting(game);
	mlx_key_hook(game->mlx, all_keyhooks, game);
}
