/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:39:33 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/11 17:09:45 by mmaksimo         ###   ########.fr       */
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

char	*trim_whitespaces(char *line, const char *charset)
{
	char	*tmp_line;

	tmp_line = line;
	line = ft_strtrim(tmp_line, charset);
	free(tmp_line);
	tmp_line = NULL;
	return (line);
}

bool	check_unique(t_unique *unique, int height)
{
	if (unique->n == 1)
		unique->all++;
	if (unique->s == 1)
		unique->all++;
	if (unique->e == 1)
		unique->all++;
	if (unique->w == 1)
		unique->all++;
	if (unique->c == 1)
		unique->all++;
	if (unique->f == 1)
		unique->all++;
	if (height)
		unique->all++;
	if (unique->all != 7)
		return (false);
	return (true);
}
