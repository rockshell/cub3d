/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:14:41 by mmaksimo          #+#    #+#             */
/*   Updated: 2025/03/06 00:59:09 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;
	size_t	trim_len;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (start < ft_strlen(s1) && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end > start && ft_strchr(set, s1[end]) != NULL)
		end--;
	trim_len = end - start + 2;
	trim = (char *) malloc(trim_len * sizeof(char));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, &s1[start], trim_len);
	return (trim);
}
