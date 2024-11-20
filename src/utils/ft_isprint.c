/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:50:30 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/20 09:12:49 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isbashchars(int c)
{
	if (c != 124 && c != 60 && c != 62 && c != '\"' && c != '\'')
		return (1);
	return (0);
}

int	ft_isprint(int c)
{
	if ((c > 32 && c <= 126) && ft_isbashchars(c))
		return (1);
	return (0);
}

int	is_cmd(int c)
{
	if ((c > 32 && c <= 126) && c != 124 && c != 60 && c != 62)
		return (1);
	return (0);
}
