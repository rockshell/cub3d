/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:13:27 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/11 17:03:56 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path(t_game *game, char *line, int fd)
{
	char	*path;
	int		fd_test;

	path = line + 2;
	while (ft_isspace(*path))
		path++;
	if (!ft_strendswith(path, ".png"))
		error_exit(game, line, fd, 1);
	fd_test = open(path, O_RDONLY);
	if (fd_test < 0)
	{
		close(fd_test);
		error_exit(game, line, fd, 8);
	}
	close(fd_test);
	return (path);
}

void	process_tex_path(int dir, int *depth, t_err_group *group)
{
	t_game	*game;
	char	*line;
	int		fd;

	game = group->game;
	line = group->line;
	fd = group->fd;
	game->tex_path[dir] = ft_strdup(get_path(game, line, fd));
	if (!group->game->tex_path[dir])
		error_exit(game, line, fd, 0);
	*depth += 1;
}

bool	get_texture(t_err_group *group, int *depth, t_unique *unique)
{
	if (ft_strncmp(group->line, "NO", 2) == 0 && unique->n == 0)
	{
		process_tex_path(NO, depth, group);
		unique->n += 1;
	}
	else if (ft_strncmp(group->line, "SO", 2) == 0 && unique->s == 0)
	{
		process_tex_path(SO, depth, group);
		unique->s += 1;
	}
	else if (ft_strncmp(group->line, "EA", 2) == 0 && unique->e == 0)
	{
		process_tex_path(EA, depth, group);
		unique->e += 1;
	}
	else if (ft_strncmp(group->line, "WE", 2) == 0 && unique->w == 0)
	{
		process_tex_path(WE, depth, group);
		unique->w += 1;
	}
	else
		return (false);
	return (true);
}
