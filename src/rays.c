/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arch <arch@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:54 by arch              #+#    #+#             */
/*   Updated: 2025/03/21 19:35:25 by arch             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		hit_the_wall(t_ray ray, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(ray.ray_x/TILE_SIZE);
	map_y = (int)(ray.ray_y/TILE_SIZE);
	// map_x = (int)(ray.ray_x);
	// map_y = (int)(ray.ray_y);
	// printf("%c\n", game->map[map_x][map_y]);
	if (game->map[map_x][map_y] == '1')
	{
		printf("Map X: %i\nMap Y: %i\n", map_x, map_y);
		printf("Hit the wall!\n");
		return (1);
	}
	return (0);
	
}

double	degree_to_radians(double degree)
{
	return (degree * M_PI / 180);
}

int		wall_height(double distance)
{
	return(floor(HALF_HEIGHT/distance));
}

void	draw_wall(double distance, int width, t_game *game)
{
	int	i;
	int height;

	i = HALF_HEIGHT;
	height = (wall_height(distance));
	while (i > HALF_HEIGHT-(height/2))
	{
		mlx_put_pixel(game->img, width, i, 0x000000);
		i--;
	}
	i = HALF_HEIGHT;
	while (i < HALF_HEIGHT+(height/2))
	{
		mlx_put_pixel(game->img, width, i, 0x000000);
		i++;
	}
}

void	ray_casting(t_game *game)
{
	int		ray_count;
	double	ray_angle;
	double	ray_sin;
	double	ray_cos;
	double	ray_distance;
	t_ray	current_ray;

	ray_count = -1;
	// ray_distance = 0.0;
	ray_angle = (double) game->player_angle_view - HALF_FOV;

	while (++ray_count < WIN_WIDTH)
	{
		current_ray.ray_x = game->player_pos_x;
		current_ray.ray_y = game->player_pos_y;
		ray_cos = cos(degree_to_radians(ray_angle))/PRECISION;
		ray_sin = sin(degree_to_radians(ray_angle))/PRECISION;
		// printf("Cos: %f\nSin: %f\n", ray_cos, ray_sin);
		while (!hit_the_wall(current_ray, game))
		{
			current_ray.ray_x += ray_cos;
			current_ray.ray_y += ray_sin;
			// usleep(1000);
		}
		printf("ray_x: %lf\nray_y: %lf\n", current_ray.ray_x, current_ray.ray_y);
		printf("player_pos_x: %lf\nplayer_pos_y: %lf\n", game->player_pos_x, game->player_pos_y);
		
		ray_distance = sqrt(pow(current_ray.ray_x - game->player_pos_x, 2.0) + 
                    pow(current_ray.ray_y - game->player_pos_y, 2.0));
		// ray_distance = pow(current_ray.ray_x - game->player_pos_x, 2.0) + 
        //             pow(current_ray.ray_y - game->player_pos_y, 2.0);
		printf("Ray angle: %f\n", ray_angle);
		printf("Ray count: %i\n", ray_count);
		printf("Ray distance: %lf\n", ray_distance);
		printf("Wall height: %i\n", wall_height(ray_distance));
		draw_wall(ray_distance, ray_count, game);

		// usleep(20000);
		ray_angle += (double)FOV/WIN_WIDTH;
	}
	
	
	


}