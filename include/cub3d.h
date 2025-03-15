/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:15:15 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/15 17:14:04 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

#define WIN_WIDTH	640
#define WIN_HEIGHT	480

enum	e_side
{
	NO,
	SO,
	EA,
	WE
};

typedef struct	s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_rgb;


typedef struct	s_game
{
	char	*tex_path_nsew[4];
	
	t_rgb	floor_color;
	t_rgb	ceil_color;

	int		map_width;
	int		map_height;
	char	**map;
	
}	t_game;

typedef struct	s_error
{
	char	*line;
	t_game	*game;
	int		fd;
}	t_error;


char	*get_next_line(int fd);

int		get_map(int argc, char *filepath, t_game *game);

/* utils.c */ 
int		cube_atoi(const char *nptr);


void	free_game(t_game *game);
void	free_exit(char *line, t_game *game, int fd);

//error.c
int		check_args_get_fd(int argc, char *filepath);
void	error_exit(t_error error_s, int error_code);


#endif