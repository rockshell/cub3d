/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:00:39 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/09 19:49:39 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_player_angle(char direction)
{
	if (direction == 'N')
		return (270);
	else if (direction == 'E')
		return (0);
	else if (direction == 'S')
		return (90);
	else if (direction == 'W')
		return (180);
	return (-1);
}

void	get_player_data(t_game *game, bool *player, int i, int j)
{
	if (ft_strchr("NSWE", game->map[i][j]) && *player)
	{
		printf("Error\nBad player\n");
		free_game(game);
		exit(1);
	}
	else if (ft_strchr("NSWE", game->map[i][j]) && !*player)
	{
		*player = true;
		game->plr_pos_x = (double) j;
		game->plr_pos_y = (double) i;
		game->start_dir = game->map[i][j];
		game->plr_angle = get_player_angle(game->start_dir);
		if (game->plr_angle < 0)
		{
			printf("Error\nBad player\n");
			free_game(game);
			exit(1);
		}
	}
}

void	init_player(t_game *game)
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
			get_player_data(game, &player, i, j);
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
