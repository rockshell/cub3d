/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulikov <akulikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:02:02 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/11 17:18:14 by akulikov         ###   ########.fr       */
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

int	get_rgb_values(t_rgba *rgba, char *sub_seq, int sub_count)
{
	int	color_value;

	color_value = cube_atoi(sub_seq);
	if (color_value < 0)
	{
		free(sub_seq);
		return (-1);
	}
	if (sub_count == 0)
		rgba->r = (uint32_t) color_value;
	else if (sub_count == 1)
		rgba->g = (uint32_t) color_value;
	else if (sub_count == 2)
		rgba->b = (uint32_t) color_value;
	return (0);
}

void	init_rgba(t_rgba *rgba)
{
	rgba->r = 0x00;
	rgba->g = 0x00;
	rgba->b = 0x00;
	rgba->a = 0x00;
}

void	go_over_color_palette(int *sub_len, char *sub_seq, char *rgb_seq)
{
	sub_seq[*sub_len] = *rgb_seq;
	(*sub_len)++;
	rgb_seq++;
}

static t_rgba	parse_color(char *rgb_seq, t_game *game, char *line, int fd)
{
	t_rgba	rgba;
	int		sub_len;
	int		sub_count;
	char	*sub_seq;

	init_rgba(&rgba);
	sub_count = -1;
	sub_seq = malloc(sizeof(char) * ft_strlen(rgb_seq));
	while (*rgb_seq)
	{
		sub_len = 0;
		while (*rgb_seq && ft_isdigit(*rgb_seq))
		{
			// go_over_color_palette(&sub_len, sub_seq, rgb_seq);
			sub_seq[sub_len] = *rgb_seq;
			sub_len++;
			rgb_seq++;
		}
		sub_count++;
		sub_seq[sub_len] = '\0';
		if (get_rgb_values(&rgba, sub_seq, sub_count) < 0)
			error_exit(game, line, fd, 7);
		if (*rgb_seq)
			rgb_seq++;
	}
	free(sub_seq);
	return (rgba);
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
	color.a = 0xFF;
	out_color = (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
	return (out_color);
}
