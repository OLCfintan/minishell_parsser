/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:38:47 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/21 05:12:51 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_char(char *s1, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	if (c == 0)
		return (s1);
	str = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	str[j++] = c;
	str[j] = '\0';
	free(s1);
	return (str);
}
