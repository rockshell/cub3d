/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:15:15 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/11 17:09:59 by mmaksimo         ###   ########.fr       */
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

# define WIN_WIDTH		3840
# define WIN_HEIGHT		2160
# define HALF_HEIGHT	1080
# define FOV			60
# define HALF_FOV		30
# define PREC			1000
# define TURN_RATIO		1

enum	e_side
{
	NO,
	SO,
	EA,
	WE
};

typedef struct s_unique
{
	int	n;
	int	s;
	int	e;
	int	w;
	int	c;
	int	f;
	int	all;
}	t_unique;

typedef struct s_rgba
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
}	t_rgba;

typedef struct s_ray
{
	double	ray_x;
	double	ray_y;
	double	ray_sin;
	double	ray_cos;
}	t_ray;

typedef struct s_walls
{
	double	*walls_arr;
	int		*side;
}	t_walls;

typedef struct s_tex_pos
{
	int	x;
	int	y;
}	t_tex_pos;

typedef struct s_game
{
	char		**tex_path;
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
	mlx_image_t	*current_frame;
	mlx_image_t	*prev_frame;
	mlx_image_t	*image[4];
	t_walls		*walls;
	int			*tex_pos_x_arr;
	int			tex_width;
	int32_t		cursr_last_x;
	int32_t		cursr_last_y;
}	t_game;

typedef struct s_err_group
{
	t_game	*game;
	char	*line;
	int		fd;
}	t_err_group;

//init.c
int			init_struct(t_game *game);
void		init_assets(t_game *game);

// player.c
void		init_player(t_game *game);

//parsing.c
int			read_map(int argc, char *filepath, t_game *game);

// get_path.c
bool		get_texture(t_err_group *group, int *depth, t_unique *unique);

// get_color.c
uint32_t	get_color(t_game *game, char *line, int fd);

// get_map.c
void		get_map_and_width(t_game *game, int fd, int depth);
void		check_open_walls(t_game *game);

//render.c
void		render_game(void *param);

// controls.c
void		key_hooks(mlx_key_data_t keydata, void *param);
void		cursor_hook(double xpos, double ypos, void *param);

// controls2.c
bool		k_hold(mlx_key_data_t keydata);
void		move_ray(double *ray_x, double *ray_y, enum keys key, t_game *game);

// utils.c
int			cube_atoi(const char *nptr);
double		deg_to_rad(double degree);
int			get_text_x_pos(t_game *game, t_ray curr_ray);
char		*trim_whitespaces(char *line, const char *charset);
bool		check_unique(t_unique *unique, int height);

// cleanup.c
void		free_game(t_game *game);
void		free_exit(t_game *game, char *line, int fd);

//error.c
int			check_args_get_fd(int argc, char *filepath);
void		error_exit(t_game *game, char *line, int fd, int error_code);
void		ft_mlxerror(t_game *game);

//rays.c
void		ray_casting(t_game *game);
int			hit_the_wall(t_ray ray, t_game *game);

#endif