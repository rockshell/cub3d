/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:53:38 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/04/10 15:46:37 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(t_game *game, char *line, int fd, int error_code)
{
	if (error_code == 0)
		printf("Error\nAllocation failed\n");
	else if (error_code == 1)
		printf("Error\nInvalid texture format\n");
	else if (error_code == 2)
		printf("Error\nInvalid color format\n");
	else if (error_code == 3)
		printf("Error\nInvalid map format: open wall\n");
	else if (error_code == 4)
		printf("Error\nInvalid map format: non-unique arguments\n");
	else if (error_code == 5)
		printf("Error\nInvalid map format: char not from set \" NSWE10\"\n");
	else if (error_code == 6)
		printf("Error\nInvalid map format\n");
	else if (error_code == 7)
		printf("Error\nInvalid color value\n");
	else if (error_code == 8)
		printf("Error\nFile corrupted or does not exist\n");
	else if (error_code == 9)
		printf("Error\nBad player\n");
	free_exit(game, line, fd);
}

int	check_args_get_fd(int argc, char *filepath)
{
	int	fd;

	if (argc != 2)
	{
		errno = EINVAL;
		perror("Error\nProgram accepts only 1 argument\n");
		return (-1);
	}
	if (ft_strendswith(filepath, ".cub") == 0)
	{
		errno = EINVAL;
		perror("Error\nFile must be of type '.cub'\n");
		return (-1);
	}
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		errno = EBADF;
		perror("Error\nCould not open file");
		return (-1);
	}
	return (fd);
}

void	ft_mlxerror(t_game *game)
{
	free_game(game);
	perror(mlx_strerror(mlx_errno));
	exit(1);
}
