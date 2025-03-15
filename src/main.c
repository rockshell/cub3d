/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:12:32 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/15 23:12:46 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct(t_game *game)
{
	game->ceil_color.r = 0;
	game->ceil_color.g = 0;
	game->ceil_color.b = 0;

		
	game->player_pos_x = 0;
	game->player_pos_y = 0;

	return ;
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
	// Set up player initial position
	// Initialize game window
	// Set up game loop
	// Handle cleanup
	free_game(game);
	return (EXIT_SUCCESS);
}