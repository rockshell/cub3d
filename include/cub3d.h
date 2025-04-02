/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:15:15 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/02 16:14:18 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include "libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WIN_WIDTH		1920
# define WIN_HEIGHT		1080
# define HALF_HEIGHT	(WIN_HEIGHT / 2)
# define FOV			60
# define HALF_FOV		(FOV / 2)
# define PREC			1000
// # define TILE_SIZE		64

enum	e_side
{
	NO,
	SO,
	EA,
	WE
};

typedef struct s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_rgb;

typedef struct s_ray
{
	double	ray_x;
	double	ray_y;
	double	ray_sin;
	double	ray_cos;
}	t_ray;

typedef struct s_assets
{
	mlx_image_t		*n_image;
	mlx_image_t		*s_image;
	mlx_image_t		*w_image;
	mlx_image_t		*e_image;
}	t_assets;

typedef struct s_game
{
	char		**texture_path_nsew;
	uint32_t	ceil_color;
	uint32_t	floor_color;
	int			map_width;
	int			map_height;
	char		**map;
	double		plr_pos_x;
	double		plr_pos_y;
	int			plr_angle;
	char		start_dir;
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t *prev_frame;
	t_assets	*assets;
	double		*walls_arr;
	int			*tex_pos_x_arr;
}	t_game;


typedef struct s_error
{
	char	*line;
	t_game	*game;
	int		fd;
}	t_error;

//init
int	init_struct(t_game *game);


//readmap
char	*get_next_line(int fd);
int		read_map(int argc, char *filepath, t_game *game);

//render.c
void	render_game(void *param);
void	draw_wall(double distance, int width, t_game *game);

// controls.c
void	all_keyhooks(mlx_key_data_t keydata, void *param);

/* utils.c */
int		cube_atoi(const char *nptr);

void	free_game(t_game *game);
void	free_exit(t_error error_s);

//error.c
int		check_args_get_fd(int argc, char *filepath);
void	error_exit(t_error error_s, int error_code);
void	ft_mlxerror(t_game *game);

//rays.c
void	ray_casting(t_game *game);
double	deg_to_rad(double degree);
int		hit_the_wall(t_ray ray, t_game *game);

#endif