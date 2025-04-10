/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:01:08 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/09 22:23:20 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_pixel_color(mlx_image_t *wall_image, int x, int y)
{
	int			index;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	alpha;

	index = (y * wall_image->width + x) * 4 ;
	red = ((uint8_t)(wall_image->pixels[index])) << 24;
	green = ((uint8_t)(wall_image->pixels[index + 1])) << 16;
	blue = ((uint8_t)(wall_image->pixels[index + 2])) << 8;
	alpha = wall_image->pixels[index + 3];
	return (red | green | blue | alpha);
}

void	put_pixel(t_game *game, int height, int width, mlx_image_t *w_image)
{
	int			w_start;
	int			tex_pos_x;
	int			tex_pos_y;
	double		w_height;
	uint32_t	color;

	tex_pos_x = game->tex_pos_x_arr[width];
	w_height = floor(HALF_HEIGHT / game->walls->walls_arr[width]);
	w_start = HALF_HEIGHT - w_height / 2;
	if (height < w_start)
		mlx_put_pixel(game->current_frame, width, height, game->ceil_color);
	else if (height > w_start + w_height)
		mlx_put_pixel(game->current_frame, width, height, game->floor_color);
	else
	{
		tex_pos_y = (int)((height - w_start - 1) / w_height * w_image->height);
		color = get_pixel_color(w_image, tex_pos_x, tex_pos_y);
		mlx_put_pixel(game->current_frame, width, height, color);
	}
}

void	put_column(t_game *game, int width, mlx_image_t *wall_image)
{
	int	height;

	height = -1;
	while (++height < WIN_HEIGHT)
		put_pixel(game, height, width, wall_image);
}

mlx_image_t	*render_frame(t_game *game)
{
	int			i;
	mlx_image_t	*frame;
	mlx_image_t	*wall_image;

	i = -1;
	frame = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->current_frame = frame;
	while (++i < WIN_WIDTH)
	{
		if (game->walls->side[i] == 0)
			wall_image = game->image[NO];
		else if (game->walls->side[i] == 1)
			wall_image = game->image[SO];
		else if (game->walls->side[i] == 2)
			wall_image = game->image[EA];
		else
			wall_image = game->image[WE];
		put_column(game, i, wall_image);
	}
	return (frame);
}

void	render_game(void *param)
{
	t_game		*game;
	mlx_image_t	*current_frame;

	game = (t_game *)param;
	ray_casting(game);
	current_frame = render_frame(game);
	mlx_image_to_window(game->mlx, game->current_frame, 0, 0);
	if (game->prev_frame)
		mlx_delete_image(game->mlx, game->prev_frame);
	game->prev_frame = current_frame;
}
