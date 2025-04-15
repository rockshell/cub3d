/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulikov <akulikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:06 by arch              #+#    #+#             */
/*   Updated: 2025/04/15 15:22:16 by akulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_struct(t_game *game)
{
	int	i;

	game->tex_path = malloc(sizeof(char *) * 4);
	if (!game->tex_path)
		return (-1);
	i = 0;
	while (i < 4)
	{
		game->tex_path[i] = NULL;
		i++;
	}
	game->ceil_color = 0;
	game->floor_color = 0;
	game->plr_pos_x = 0.0;
	game->plr_pos_y = 0.0;
	game->cursr_last_x = 0;
	game->cursr_last_y = 0;
	game->map = NULL;
	game->prev_frame = NULL;
	game->walls = malloc(sizeof(t_walls));
	game->walls->side = malloc(sizeof(int) * WIN_WIDTH);
	game->walls->walls_arr = malloc(sizeof(double) * WIN_WIDTH);
	game->tex_pos_x_arr = malloc(sizeof(int) * WIN_WIDTH);
	game->map_height = 0;
	return (0);
}

static int	get_avrg_width(t_game *game)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 4)
	{
		sum += game->image[i]->width;
		i++;
	}
	return (sum / i);
}

void	init_assets(t_game *game)
{
	mlx_texture_t	*n_texture;
	mlx_texture_t	*s_texture;
	mlx_texture_t	*w_texture;
	mlx_texture_t	*e_texture;

	n_texture = mlx_load_png(game->tex_path[NO]);
	s_texture = mlx_load_png(game->tex_path[SO]);
	e_texture = mlx_load_png(game->tex_path[EA]);
	w_texture = mlx_load_png(game->tex_path[WE]);
	game->image[NO] = mlx_texture_to_image(game->mlx, n_texture);
	game->image[SO] = mlx_texture_to_image(game->mlx, s_texture);
	game->image[EA] = mlx_texture_to_image(game->mlx, e_texture);
	game->image[WE] = mlx_texture_to_image(game->mlx, w_texture);
	game->tex_width = get_avrg_width(game);
	mlx_delete_texture(n_texture);
	mlx_delete_texture(s_texture);
	mlx_delete_texture(e_texture);
	mlx_delete_texture(w_texture);
}
