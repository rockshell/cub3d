/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:54 by arch              #+#    #+#             */
/*   Updated: 2025/03/26 20:00:22 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_the_wall(t_ray ray, t_game *game)
{
	int	map_x;
	int	map_y;
	
	// map_x = (int)(ray.ray_x/TILE_SIZE);
	// map_y = (int)(ray.ray_y/TILE_SIZE);
	map_x = (int)(ray.ray_x);
	map_y = (int)(ray.ray_y);
	// printf("Map X: %i\nMap Y: %i\n", map_x, map_y);
	if (game->map[map_y][map_x] == '1')
	{
		printf("Map X: %i\nMap Y: %i\n", map_x, map_y);
		// printf("Type: %c\n", game->map[map_x][map_y]);
		printf("Hit the wall!\n");
		return (1);
	}
	return (0);
}

double	deg_to_rad(double degree)
{
	return (degree * M_PI / 180);
}

double	fix_fisheye(t_game *game, double distance, double ray_angle)
{
	double	corrected_distance;
	double	beta_angle;

	beta_angle = fabs(ray_angle - game->plr_angle);
	corrected_distance = distance * cos(deg_to_rad(beta_angle));
	return (corrected_distance);
}

void	ray_casting(t_game *game)
{
	int		ray_count;
	double	ray_angle;
	double	ray_distance;
	t_ray	curr_ray;

	ray_count = -1;
	ray_angle = (double) game->plr_angle - HALF_FOV;
	while (++ray_count < WIN_WIDTH)
	{
		curr_ray.ray_x = game->plr_pos_x;
		curr_ray.ray_y = game->plr_pos_y;
		curr_ray.ray_cos = cos(deg_to_rad(ray_angle)) / PREC;
		curr_ray.ray_sin = sin(deg_to_rad(ray_angle)) / PREC;
		while (!hit_the_wall(curr_ray, game))
		{
			curr_ray.ray_x += curr_ray.ray_cos;
			curr_ray.ray_y += curr_ray.ray_sin;
		}
		ray_distance = sqrt(pow(curr_ray.ray_x - game->plr_pos_x, 2.0)
				+ pow(curr_ray.ray_y - game->plr_pos_y, 2.0));
		ray_distance = fix_fisheye(game, ray_distance, ray_angle);
		draw_wall(ray_distance, ray_count, game);
		ray_angle += (double) FOV / WIN_WIDTH;
	}
}
