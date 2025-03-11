/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:39:33 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/11 19:39:57 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	cube_atoi(const char *nptr)
{
	long int		num;
	unsigned int	i;

	num = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		return (-1);
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		num = (num + (nptr[i] - 48)) * 10;
		if (num > INT_MAX)
			return (-1);
		i++;
	}
	num /= 10;
	if (nptr[i] != '\0' || num > 255)
		return (-1);
	return ((int) num);
}
