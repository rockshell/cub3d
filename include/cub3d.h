/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:15:15 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/06 03:16:47 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

#define WIN_WIDTH	640
#define WIN_HEIGHT	480

enum	e_side
{
	NO,
	SO,
	WE,
	EA
};


typedef struct	s_game
{
	char	*tex_path_nsew[4];
	
}	t_game;


char	*get_next_line(int fd);


#endif