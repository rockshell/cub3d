/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:54 by arch              #+#    #+#             */
/*   Updated: 2025/04/06 21:57:17 by mmaksimo         ###   ########.fr       */
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

int get_side(t_ray curr_ray, t_ray prev_ray)
{
    enum e_side side;
    
    // Calculate which grid cell we're in
    int cell_x = (int)curr_ray.ray_x;
    int cell_y = (int)curr_ray.ray_y;
    
    // Calculate how far we are from the cell edges
    double dist_from_left = curr_ray.ray_x - cell_x;
    double dist_from_top = curr_ray.ray_y - cell_y;
    
    // These small values mean we're very close to an edge
    double threshold = 0.01;
    
    if (dist_from_left < threshold) {
        // Close to left edge = EAST-facing wall
        side = EA;
    } else if (dist_from_left > 0.99) {
        // Close to right edge = WEST-facing wall
        side = WE;
    } else if (dist_from_top < threshold) {
        // Close to top edge = NORTH-facing wall
        side = NO;
    } else if (dist_from_top > 0.99) {
        // Close to bottom edge = SOUTH-facing wall
        side = SO;
    } else {
        // If we can't determine by position, use direction of movement
        double dx = fabs(curr_ray.ray_x - prev_ray.ray_x);
        double dy = fabs(curr_ray.ray_y - prev_ray.ray_y);
        
        if (dx > dy) {
            // We moved more horizontally
            if (curr_ray.ray_cos > 0) {
                side = WE; // Moving right, hit west face
            } else {
                side = EA; // Moving left, hit east face
            }
        } else {
            // We moved more vertically
            if (curr_ray.ray_sin > 0) {
                side = NO; // Moving down, hit north face
            } else {
                side = SO; // Moving up, hit south face
            }
        }
    }
    
    return (side);
}

void	ray_casting(t_game *game)
{
	int		ray_count;
	double	ray_angle;
	double	ray_dist;
	t_ray	curr_ray;
	t_ray	prev_ray;

	ray_count = -1;
	ray_angle = (double) game->plr_angle - HALF_FOV;
	while (++ray_count < WIN_WIDTH)
	{
		curr_ray.ray_x = game->plr_pos_x;
		curr_ray.ray_y = game->plr_pos_y;
		prev_ray.ray_x = curr_ray.ray_x;
		prev_ray.ray_y = curr_ray.ray_y;
		curr_ray.ray_cos = cos(deg_to_rad(ray_angle)) / PREC;
		curr_ray.ray_sin = sin(deg_to_rad(ray_angle)) / PREC;
		while (!hit_the_wall(curr_ray, game))
		{
			prev_ray.ray_x = curr_ray.ray_x;
			prev_ray.ray_y = curr_ray.ray_y;
			curr_ray.ray_x += curr_ray.ray_cos;
			curr_ray.ray_y += curr_ray.ray_sin;
		}
		ray_dist = sqrt(pow(curr_ray.ray_x - game->plr_pos_x, 2.0)
				+ pow(curr_ray.ray_y - game->plr_pos_y, 2.0));
		ray_dist = fix_fisheye(game, ray_dist, ray_angle);
		
		game->walls->walls_arr[ray_count] = ray_dist;
		game->walls->side[ray_count] = get_side(curr_ray, prev_ray);
		game->tex_pos_x_arr[ray_count] = (int) floor(32 * (curr_ray.ray_x + curr_ray.ray_y)) % 32;
		ray_angle += (double) FOV / WIN_WIDTH;
	}
}
