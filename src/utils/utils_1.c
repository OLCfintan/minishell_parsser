/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:50:43 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/15 01:49:07 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count != 0 && size > (SIZE_MAX / count))
		return (NULL);
	str = malloc(size * count);
	if (!str)
		return (NULL);
	ft_bzero(str, (count * size));
	return (str);
}

int	ft_isbashchars(int c)
{
	if (c != 124 && c != 60 && c != 62 && c != 39 && c != 34)
		return (1);
	return (0);
}

int	ft_isprint(int c)
{
	if ((c > 32 && c <= 126) && ft_isbashchars(c))
		return (1);
	return (0);
}

int	ft_iswp(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}