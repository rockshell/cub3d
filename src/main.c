/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:12:32 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/06 03:16:47 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_struct(t_game *game)
{
	(void) game;
	return ;
}

void	free_exit(char *line, t_game *game, int fd)
{
	free(line);
	free(game);
	close(fd);
	exit(EXIT_FAILURE);	
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char *get_path(char *line, t_game *game, int fd)
{
	char	*path;
	int		fd_test;
	
	path = line + 2;
	// both absolute and relative are valid. need to check the existence of file as well
	while (ft_isspace(*path))
		path++;
	// MAYBE NOT THE BEST WAY HERE...
	path[ft_strlen(path) - 1] = '\0';
	if (!ft_strendswith(path, ".xpm"))
	{
		printf("Error\nInvalid texture format");
		free_exit(line, game, fd);
	}

	fd_test = open(path, O_RDONLY);
	if (fd_test < 0)
	{
		printf("Error\nInvalid file path");
		close(fd_test);
		free_exit(line, game, fd);
	}
	close(fd_test);
		// printf("%s\n", path);

	return (path);
}


int	get_map(int argc, char *filepath, t_game *game)
{
	// Check argument count (exactly 2 arguments: executable and map file)
	if (argc != 2)
	{
		errno = EINVAL;
		perror("Error\nProgram accepts only 1 argument");
		
		// free game;
		return (-1);
	}
	
	// Validate map file extension (.cub)
	if (ft_strendswith(filepath, ".cub") == 0)
	{
		errno = EINVAL;
		perror("Error\nFile must be of type '.cub'");
		return (-1);
	}

	// Parse and validate map file
	
	int fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		errno = EBADF;
		perror("Error\nCould not open file");
		return (-1);
	}
	
	char	*line; 
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
			
		/*
		◦ Except for the map content, each type of element can be separated by one or
		more empty line(s).

		◦ Except for the map content which always has to be the last, each type of
		element can be set in any order in the file.

		◦ Except for the map, each type of information from an element can be separated
		by one or more space(s).

		*/
		if (*line == '\n')
		{
			free(line);
			continue ;
		}

		char *tmp_line = line;
		line = ft_strtrim(tmp_line, " \t");
		free(tmp_line);

		if (ft_isdigit(*line))
		{
			free(line);
			break ;
		}
		
		 // For sides
		if (ft_strncmp(line, "NO", 2) == 0)
			game->tex_path_nsew[0] = get_path(line, game, fd);
		else if (ft_strncmp(line, "SO", 2) == 0)
			game->tex_path_nsew[1] = get_path(line, game, fd);
		else if (ft_strncmp(line, "EA", 2) == 0)
			game->tex_path_nsew[2] = get_path(line, game, fd);
		else if (ft_strncmp(line, "WE", 2) == 0)
			game->tex_path_nsew[3] = get_path(line, game, fd);
		// else
		// {
		// 	free(line);
		// 	continue ;
		// 	// printf("Error\nInvalid map element");
		// 	// free_exit(line, game, fd);
		// }
			
		// printf("%s", line);
		free(line);
		
	}
	
	for (int i = 0; i < 4; i++)
		printf("%s\n",game->tex_path_nsew[i]);

	close(fd);

	return (0);
}


int	main(int argc, char *argv[])
{
	t_game *game;

	game = malloc(sizeof(t_game));
	
	// Init game struct
	init_struct(game);
	
	// Check args, parse map
	if (get_map(argc, argv[1], game) < 0)
	{
		free(game);
		return (1);
	}


	// Start game / Create main game structure
	// Initialize MLX
	// Set up player initial position
	// Initialize game window
	// Set up game loop
	// Handle cleanup
	free(game);
	return (EXIT_SUCCESS);
}