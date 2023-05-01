/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:23:15 by amaisonn          #+#    #+#             */
/*   Updated: 2023/04/11 23:24:55 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	td;
	size_t	destl;
	size_t	srcl;

	td = ft_strlen(dest);
	destl = ft_strlen(dest);
	srcl = ft_strlen(src);
	if (size == 0 || ft_strlen(dest) >= size)
		return (ft_strlen(src) + size);
	while (*src && td < size - 1)
	{
		dest[td] = *src;
		td++;
		src++;
	}
	dest[td] = '\0';
	return (destl + srcl);
}
