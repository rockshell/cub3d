/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:42:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/11 01:34:52 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_map(t_err_group *grp, int *depth, int *unique, int *height)
{
	get_texture(grp, depth, unique);
	if (ft_strncmp(grp->line, "F", 1) == 0)
	{
		grp->game->floor_color = get_color(grp->game, grp->line, grp->fd);
		*depth += 1;
		*unique += 1;
	}
	else if (ft_strncmp(grp->line, "C", 1) == 0)
	{
		grp->game->ceil_color = get_color(grp->game, grp->line, grp->fd);
		*depth += 1;
		*unique += 1;
	}
	if (ft_strncmp(grp->line, "0", 1) == 0 && *unique == 6)
		error_exit(grp->game, grp->line, grp->fd, 3);
	else if (ft_strncmp(grp->line, "1", 1) == 0 && *unique == 6)
	{
		if (ft_strendswith(grp->line, "0"))
			error_exit(grp->game, grp->line, grp->fd, 3);
		*depth += 1;
		*height += 1;
	}
}

int	process_line(t_err_group *group, int *depth)
{
	group->line = get_next_line(group->fd);
	if (!group->line)
		return (1);
	group->line = trim_whitespaces(group->line, " \t\n\r");
	if (*group->line == '\0')
	{
		(*depth)++;
		free(group->line);
		return (2);
	}
	if (!ft_strchr("NSWEFC10", group->line[0]))
		error_exit(group->game, group->line, group->fd, 6);
	return (0);
}

void	parse_map_and_height(t_game *game, int fd, int *depth)
{
	t_err_group		group;
	int				unique;
	int				height;
	int				proc_line;

	unique = 0;
	height = 0;
	group.game = game;
	group.fd = fd;
	while (1)
	{
		proc_line = process_line(&group, depth);
		if (proc_line == 1)
			break ;
		else if (proc_line == 2)
			continue ;
		process_map(&group, depth, &unique, &height);
		free(group.line);
	}
	if (height)
		unique++;
	if (unique != 7)
		error_exit(game, group.line, fd, 4);
	game->map_height = height;
}

int	read_map(int argc, char *filepath, t_game *game)
{
	int		fd;
	int		depth;

	fd = check_args_get_fd(argc, filepath);
	if (fd < 0)
		return (-1);
	depth = 0;
	parse_map_and_height(game, fd, &depth);
	close(fd);
	game->map = malloc(sizeof(char *) * game->map_height);
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		error_exit(game, NULL, fd, 8);
	get_map_and_width(game, fd, depth);
	close(fd);
	check_open_walls(game);
	return (0);
}
