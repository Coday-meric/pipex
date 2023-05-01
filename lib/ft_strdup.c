/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:07:59 by amaisonn          #+#    #+#             */
/*   Updated: 2023/04/10 18:07:28 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		lensrc;
	char	*dest;

	lensrc = ft_strlen(src) + 1;
	dest = malloc(lensrc);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, (char *)src, lensrc);
	return (dest);
}
