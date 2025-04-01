/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arch <arch@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:12:32 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/01 20:23:10 by arch             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_assets(t_game *game)
{
	mlx_texture_t	*n_texture;
	mlx_texture_t	*s_texture;
	mlx_texture_t	*w_texture;
	mlx_texture_t	*e_texture;
	
	game->assets = malloc(sizeof(t_assets));
	if (!game->assets)
	{
		// error_exit();
		free_game(game);
	}
	n_texture = mlx_load_png(game->texture_path_nsew[0]);
	s_texture = mlx_load_png(game->texture_path_nsew[1]);
	e_texture = mlx_load_png(game->texture_path_nsew[2]);
	w_texture = mlx_load_png(game->texture_path_nsew[3]);
	game->assets->n_image = mlx_texture_to_image(game->mlx, n_texture);
	game->assets->s_image = mlx_texture_to_image(game->mlx, s_texture);
	game->assets->e_image = mlx_texture_to_image(game->mlx, e_texture);
	game->assets->w_image = mlx_texture_to_image(game->mlx, w_texture);
	mlx_delete_texture(n_texture);
	mlx_delete_texture(s_texture);
	mlx_delete_texture(e_texture);
	mlx_delete_texture(w_texture);
}

int	get_player_angle(char direction)
{
	if (direction == 'N')
		return(270);
	else if (direction == 'E')
		return(0);
	else if (direction == 'S')
		return(90);
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
				game->plr_pos_x = (double) j;
				game->plr_pos_y = (double) i;
				game->start_dir = game->map[i][j];
				game->plr_angle = get_player_angle(game->start_dir);
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

int	main(int argc, char *argv[])
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	init_struct(game);
	if (read_map(argc, argv[1], game) < 0)
	{
		free_game(game);
		return (EXIT_FAILURE);
	}
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "CUB3D", false);
	if (!game->mlx)
		ft_mlxerror(game);
	init_assets(game);
	get_player_position(game);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		ft_mlxerror(game);
	mlx_loop_hook(game->mlx, render_game, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}
