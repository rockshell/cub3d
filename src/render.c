/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arch <arch@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:01:08 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/01 21:14:52 by arch             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_column(t_game *game, mlx_image_t *frame, int width)
{
	int height;
	int wall_start;
	int wall_end;
	double distance;
	double wall_height;

	height = -1;
	distance = game->walls_arr[width];
	wall_height = floor(HALF_HEIGHT / distance);
	wall_start = HALF_HEIGHT - wall_height;
	wall_end = WIN_HEIGHT - wall_start;
	while (++height < WIN_HEIGHT)
	{
		if (height < wall_start)
			mlx_put_pixel(frame, width, height, game->ceil_color);
		else if (height >= wall_start && height <= wall_end)
			mlx_put_pixel(frame, width, height, 0xFF000000);
		else if (height > wall_end)
			mlx_put_pixel(frame, width, height, game->floor_color);
	}
}

mlx_image_t	*render_frame(t_game *game)
{
	int	i;
	mlx_image_t *frame;

	i = -1;
	frame = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	while (++i < WIN_WIDTH)
	{
		put_column(game, frame, i);
	}
	return (frame);
}

void	render_game(void *param)
{
	t_game	*game;
	mlx_image_t *current_frame;

	game = (t_game *)param;
	ray_casting(game);
	current_frame = render_frame(game);
	mlx_image_to_window(game->mlx, current_frame, 0, 0);
	if (game->prev_frame)
		mlx_delete_image(game->mlx, game->prev_frame);
	game->prev_frame = current_frame;
	mlx_key_hook(game->mlx, all_keyhooks, game);
}
