/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:11:56 by amaisonn          #+#    #+#             */
/*   Updated: 2023/04/10 18:07:28 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		lens1;
	int		lens2;
	char	*res;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	res = malloc((lens1 + lens2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, (char *)s1, lens1 + 1);
	ft_strlcat(res, (char *)s2, lens2 + lens1 + 1);
	return (res);
}
