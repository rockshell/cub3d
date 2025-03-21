/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arch <arch@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:12:32 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/21 19:04:55 by arch             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_struct(t_game *game)
{
	int	i;
	game->texture_path_nsew = malloc(sizeof(char *) * 4);
	if (!game->texture_path_nsew)
		return (-1);
	i = 0;
	while (i < 4)
	{
		game->texture_path_nsew[i] = NULL;
		i++;
	}
	game->ceil_color = 0;
	game->floor_color = 0;

	game->player_pos_x = 0.0;
	game->player_pos_y = 0.0;

	game->map = NULL;

	return (0);
}

void	ft_mlxerror(t_game *game)
{
	free_game(game);
	perror(mlx_strerror(mlx_errno));
	exit(1);
}

int		get_player_angle(char direction)
{
	if (direction == 'N')
		return(90);
	else if (direction == 'E')
		return(0);
	else if (direction == 'S')
		return(270);
	else if (direction == 'W')
		return(180);
	return (-1);
}

void	get_player_position(t_game *game)
{
	int		i;
	int		j;
	bool	player;
	
	i = 0;
	player = false;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (ft_strchr("NSWE", game->map[i][j]) && player)
			{
				printf("Error\nBad player\n");
				free_game(game);
				exit(1);
			}
			else if (ft_strchr("NSWE", game->map[i][j]) && !player)
			{
				player = true;
				game->player_pos_x = (double) j;
				game->player_pos_y = (double) i;
				game->start_dir = game->map[i][j];
				game->player_angle_view = get_player_angle(game->start_dir);
			}
			j++;
		}
		i++;
	}
	if (!player)
	{
		printf("Error\nNo player found\n");
		free_game(game);
		exit(1);
	}
}


static bool	key_pressed(mlx_key_data_t keydata)
{
	if ((keydata.action == MLX_PRESS) || (keydata.action == MLX_REPEAT))
		return (true);
	return (false);
}

static void	all_keyhooks(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	// if (keydata.key == MLX_KEY_RIGHT_BRACKET && key_pressed(keydata))
	// 	game->control->scale += 1;
	// if (keydata.key == MLX_KEY_LEFT_BRACKET && key_pressed(keydata))
	// 	game->control->scale -= 1;
	// if (keydata.key == MLX_KEY_RIGHT && key_pressed(keydata))
	// 	game->control->transpose_x += 20;
	// if (keydata.key == MLX_KEY_LEFT && key_pressed(keydata))
	// 	game->control->transpose_x -= 20;
	// if (keydata.key == MLX_KEY_UP && key_pressed(keydata))
	// 	game->control->transpose_y -= 20;
	// if (keydata.key == MLX_KEY_DOWN && key_pressed(keydata))
	// 	game->control->transpose_y += 20;
	// if (keydata.key == MLX_KEY_PAGE_UP && key_pressed(keydata))
	// 	game->control->rotate -= 0.1;
	// if (keydata.key == MLX_KEY_PAGE_DOWN && key_pressed(keydata))
	// 	game->control->rotate += 0.1;
	// if (keydata.key == MLX_KEY_EQUAL && key_pressed(keydata))
	// 	game->control->stretch += 0.5;
	// if (keydata.key == MLX_KEY_MINUS && key_pressed(keydata))
	// 	game->control->stretch -= 0.5;
	if (keydata.key == MLX_KEY_ESCAPE && key_pressed(keydata))
		mlx_close_window(game->mlx);
}

static void	render_bg(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			if (i < WIN_HEIGHT / 2)
				mlx_put_pixel(game->img, j, i, game->ceil_color);
			else
				mlx_put_pixel(game->img, j, i, game->floor_color);
			j++;
		}
		i++;
	}
}

void	render_control(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	render_bg((t_game *)game);
	ray_casting(game);
	// render_walls((t_game *)game);
	mlx_key_hook(game->mlx, all_keyhooks, game);
}

int	main(int argc, char *argv[])
{
	t_game *game;

	game = malloc(sizeof(t_game));
	
	// Init game struct
	init_struct(game);
	
	// Check args, parse map
	if (read_map(argc, argv[1], game) < 0)
	{
		free_game(game);
		return (EXIT_FAILURE);
	}
	

	// Start game / Create main game structure
	// Initialize MLX
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "CUB3D", true);
	if (!game->mlx)
		ft_mlxerror(game);

	// Get player initial position
	get_player_position(game);
	printf("player_pos_x:	%lf\n", game->player_pos_x);
	printf("player_pos_y:	%lf\n", game->player_pos_y);
	printf("start dir:	%c\n", game->start_dir);
	
	// Initialize game window
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		ft_mlxerror(game);
	// Set up game control hooks and loop
	// game->control = (t_control *)malloc(sizeof(t_control));
	// init_params(game->control, line_cnt, game->elem_cnt);
	mlx_loop_hook(game->mlx, render_control, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	// Handle cleanup
	free_game(game);
	return (EXIT_SUCCESS);
}