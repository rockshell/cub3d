/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulikov <akulikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:42:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/15 13:14:19 by akulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_color(t_err_group *grp, int *depth, t_unique *unique)
{
	if (ft_strncmp(grp->line, "F", 1) == 0 && unique->f == 0)
	{
		grp->game->floor_color = get_color(grp->game, grp->line, grp->fd);
		*depth += 1;
		unique->f += 1;
		return (true);
	}
	else if (ft_strncmp(grp->line, "C", 1) == 0 && unique->c == 0)
	{
		grp->game->ceil_color = get_color(grp->game, grp->line, grp->fd);
		*depth += 1;
		unique->c += 1;
		return (true);
	}
	return (false);
}

void	process_map(t_err_group *grp, int *depth, t_unique *unique, int *height)
{
	if (get_texture(grp, depth, unique))
		return ;
	if (parse_color(grp, depth, unique))
		return ;
	if (ft_strncmp(grp->line, "0", 1) == 0)
		error_exit(grp->game, grp->line, grp->fd, 3);
	else if (ft_strncmp(grp->line, "1", 1) == 0)
	{
		if (ft_strendswith(grp->line, "0"))
			error_exit(grp->game, grp->line, grp->fd, 3);
		*depth += 1;
		*height += 1;
		return ;
	}
	error_exit(grp->game, grp->line, grp->fd, 4);
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

void	parse_map_and_height(t_game *game, int fd, int *depth, t_unique *unique)
{
	t_err_group		group;
	int				height;
	int				proc_line;

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
		process_map(&group, depth, unique, &height);
		free(group.line);
	}
	if (!check_unique(unique, height))
		error_exit(game, group.line, fd, 4);
	game->map_height = height;
}

int	read_map(int argc, char *filepath, t_game *game)
{
	int			fd;
	int			depth;
	t_unique	unique;

	unique.n = 0;
	unique.s = 0;
	unique.e = 0;
	unique.w = 0;
	unique.c = 0;
	unique.f = 0;
	unique.all = 0;
	fd = check_args_get_fd(argc, filepath);
	if (fd < 0)
		return (-1);
	depth = 0;
	parse_map_and_height(game, fd, &depth, &unique);
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
