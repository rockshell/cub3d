/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:39:33 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/09 20:57:00 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cube_atoi(const char *nptr)
{
	long int		num;
	unsigned int	i;

	num = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		return (-1);
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		num = (num + (nptr[i] - 48)) * 10;
		if (num > INT_MAX)
			return (-1);
		i++;
	}
	num /= 10;
	if (nptr[i] != '\0' || num > 255)
		return (-1);
	return ((int) num);
}

double	deg_to_rad(double degree)
{
	return (degree * M_PI / 180);
}

int	get_text_x_pos(t_game *game, t_ray curr_ray)
{
	double	ray;

	ray = curr_ray.ray_x + curr_ray.ray_y;
	return ((int)floor(game->tex_width * 2 * ray) % game->tex_width);
}

bool	k_hold(mlx_key_data_t keydata)
{
	if ((keydata.action == MLX_PRESS) || (keydata.action == MLX_REPEAT))
		return (true);
	return (false);
}

void	move_ray(double *ray_x, double *ray_y, enum keys key, t_game *game)
{
	if (key == 87)
	{
		*ray_x += cos(deg_to_rad(game->plr_angle)) / (PREC / 100);
		*ray_y += sin(deg_to_rad(game->plr_angle)) / (PREC / 100);
	}
	else if (key == 83)
	{
		*ray_x -= cos(deg_to_rad(game->plr_angle)) / (PREC / 100);
		*ray_y -= sin(deg_to_rad(game->plr_angle)) / (PREC / 100);
	}
	else if (key == 65)
	{
		*ray_x += cos(deg_to_rad(game->plr_angle - 90)) / (PREC / 100);
		*ray_y += sin(deg_to_rad(game->plr_angle - 90)) / (PREC / 100);
	}
	else if (key == 68)
	{
		*ray_x += cos(deg_to_rad(game->plr_angle + 90)) / (PREC / 100);
		*ray_y += sin(deg_to_rad(game->plr_angle + 90)) / (PREC / 100);
	}
}
