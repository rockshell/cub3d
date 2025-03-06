/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:50:22 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/06 15:50:52 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(game->tex_path_nsew[i]);
		game->tex_path_nsew[i] = NULL;
		i++;
	}
	free(game);
	game = NULL;
}

void	free_exit(char *line, t_game *game, int fd)
{
	free(line);
	line = NULL;
	free_game(game);
	close(fd);
	exit(EXIT_FAILURE);	
}
