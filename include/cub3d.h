/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulikov <akulikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:15:15 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/25 20:08:24 by akulikov         ###   ########.fr       */
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

#define WIN_WIDTH	1920
#define WIN_HEIGHT	1440
#define HALF_HEIGHT	(WIN_HEIGHT / 2)
#define FOV			60
#define	HALF_FOV	(FOV / 2)
#define PRECISION	1000
#define	TILE_SIZE	64
// #define PI 			3.14159265359

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

typedef struct s_ray
{
	double	ray_x;
	double	ray_y;
}	t_ray;

typedef struct	s_game
{
	char		**texture_path_nsew;
		
	uint32_t	ceil_color;
	uint32_t	floor_color;
	
	int			map_width;
	int			map_height;
	char		**map;
		
	double		player_pos_x;
	double		player_pos_y;
	int			player_angle_view;
	char		start_dir;

	mlx_t		*mlx;
	mlx_image_t	*img;

}	t_game;

typedef struct	s_error
{
	char	*line;
	t_game	*game;
	int		fd;
}	t_error;





char	*get_next_line(int fd);

int		read_map(int argc, char *filepath, t_game *game);

/* utils.c */ 
int		cube_atoi(const char *nptr);


void	free_game(t_game *game);
void	free_exit(t_error error_s);

//error.c
int		check_args_get_fd(int argc, char *filepath);
void	error_exit(t_error error_s, int error_code);

//rays.c
void	ray_casting(t_game *game);
double	degree_to_radians(double degree);



#endif