/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:01:08 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/10 16:11:38 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


uint32_t get_pixel_color(mlx_image_t *wall_image, double distance, int x, int y)
{
	int			index;
	t_rgba		rgba;
	uint32_t	color;
	double		k_depth;

	k_depth = 1.0 / (1.0 + distance * 0.05);
	index = (y *  wall_image->width + x) * 4 ;
	rgba.r = ((uint32_t) (wall_image->pixels[index] * k_depth)) << 24;
	rgba.g = ((uint32_t) (wall_image->pixels[index + 1] * k_depth)) << 16;
	rgba.b = ((uint32_t) (wall_image->pixels[index + 2] * k_depth)) << 8;
	rgba.a = wall_image->pixels[index + 3];
	color = rgba.r | rgba.g | rgba.b | rgba.a ;
	return (color);
}

void	put_column(t_game *game, mlx_image_t *frame, int width, mlx_image_t *wall_image)
{
	int height;
	int wall_start;
	int wall_end;
	int tex_pos_x;
	int tex_pos_y;
	double distance;
	double wall_height;
	uint32_t color;

	distance = game->walls->walls_arr[width];
	tex_pos_x = game->tex_pos_x_arr[width];
	wall_height = floor(HALF_HEIGHT / distance);
	wall_start = HALF_HEIGHT - wall_height / 2;
	wall_end = wall_start + wall_height;
	height = -1;
	while (++height < WIN_HEIGHT)
	{
		if (height < wall_start)
			mlx_put_pixel(frame, width, height, game->ceil_color);
		else if (height > wall_end)
			mlx_put_pixel(frame, width, height, game->floor_color);
		else if (height >= wall_start && height <= wall_end)
		{
			tex_pos_y = (int) ((height - wall_start - 1) / wall_height * wall_image->height);
			color = get_pixel_color(wall_image, distance, tex_pos_x, tex_pos_y);
			mlx_put_pixel(frame, width, height, color);
		}
	}
}

mlx_image_t	*render_frame(t_game *game)
{
	int			i;
	mlx_image_t	*frame;
	mlx_image_t	*wall_image;

	i = -1;
	frame = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
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
		put_column(game, frame, i, wall_image);
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
	mlx_image_to_window(game->mlx, current_frame, 0, 0);
	if (game->prev_frame)
		mlx_delete_image(game->mlx, game->prev_frame);
	game->prev_frame = current_frame;
}
