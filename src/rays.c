/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:54 by arch              #+#    #+#             */
/*   Updated: 2025/04/06 16:07:53 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_the_wall(t_ray ray, t_game *game)
{
	int	map_x;
	int	map_y;
 
	map_x = (int)(ray.ray_x);
	map_y = (int)(ray.ray_y);
	if (game->map[map_y][map_x] == '1')
		return (1);
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

int	get_side(double ray_angle)
{
	int	angle;

	angle = (int)ray_angle;
	if (angle > 45 + HALF_FOV && angle <= 135 - HALF_FOV)
		return (0);
	else
		return (1);
	// else if (angle > 315 || angle <= 45)
	// 	return (2);
	// else if (angle > 135 && angle <= 225)
	// 	return (3);
}

void	ray_casting(t_game *game)
{
	int		ray_count;
	double	ray_angle;
	double	ray_dist;
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
		ray_dist = sqrt(pow(curr_ray.ray_x - game->plr_pos_x, 2.0)
				+ pow(curr_ray.ray_y - game->plr_pos_y, 2.0));
		ray_dist = fix_fisheye(game, ray_dist, ray_angle);
		
		game->walls->walls_arr[ray_count] = ray_dist;
		game->walls->side[ray_count] = get_side(ray_angle);
		game->tex_pos_x_arr[ray_count] = (int) floor(32 * (curr_ray.ray_x + curr_ray.ray_y)) % 32;
		ray_angle += (double) FOV / WIN_WIDTH;
	}
}
