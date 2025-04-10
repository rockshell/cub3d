/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:02:02 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/10 22:18:32 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_color_format(char *rgb_seq, t_game *game, char *line, int fd)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (rgb_seq[i])
	{
		if ((!ft_isdigit(rgb_seq[i]) && rgb_seq[i] != ',') || rgb_seq[0] == ','
			|| (rgb_seq[i] == ',' && !rgb_seq[i + 1])
			|| (rgb_seq[i] == ',' && rgb_seq[i + 1] == ','))
			error_exit(game, line, fd, 2);
		if (rgb_seq[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
		error_exit(game, line, fd, 2);
}

int	get_rgb_values(t_rgba *rgb, char *sub_seq, int sub_count)
{
	int	color_value;

	color_value = cube_atoi(sub_seq);
	if (color_value < 0)
	{
		free(sub_seq);
		return (-1);
	}
	if (sub_count == 0)
		rgb->r = (uint32_t) color_value;
	else if (sub_count == 1)
		rgb->g = (uint32_t) color_value;
	else if (sub_count == 2)
		rgb->b = (uint32_t) color_value;
	return (0);
}

static t_rgba	parse_color(char *rgb_seq, t_game *game, char *line, int fd)
{
	t_rgba	rgb;
	int		sub_len;
	int		sub_count;
	char	*sub_seq;

	sub_count = -1;
	sub_seq = malloc(sizeof(char) * ft_strlen(rgb_seq));
	while (*rgb_seq)
	{
		sub_len = 0;
		while (*rgb_seq && ft_isdigit(*rgb_seq))
		{
			sub_seq[sub_len] = *rgb_seq;
			sub_len++;
			rgb_seq++;
		}
		sub_count++;
		sub_seq[sub_len] = '\0';
		if (get_rgb_values(&rgb, sub_seq, sub_count) < 0)
			error_exit(game, line, fd, 7);
		if (*rgb_seq)
			rgb_seq++;
	}
	free(sub_seq);
	return (rgb);
}

uint32_t	get_color(t_game *game, char *line, int fd)
{
	t_rgba		color;
	uint32_t	out_color;
	int			i;

	i = 1;
	if (line[i])
		while (line[i] && ft_isspace(line[i]))
			i++;
	check_color_format(&line[i], game, line, fd);
	color = parse_color(&line[i], game, line, fd);
	out_color = (color.r << 24) | (color.g << 16) | (color.b << 8) | 0xFF;
	return (out_color);
}
