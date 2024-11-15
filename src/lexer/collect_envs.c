/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_envs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:38:41 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/14 19:38:42 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*lexer_get_env_value(t_lexer *lexer, char **env)
{
	char	*value;
	char	*key;
	int		i;

	i = 0;
	key = ft_strdup("");
	while (lexer->c != '\0' && ft_isprint(lexer->c))
	{
		key = ft_strjoin_char(key, lexer->c);
		lexer_advance(lexer);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
		{
			value = ft_strdup(env[i] + ft_strlen(key) + 1);
			return (free(key), value);
		}
		i++;
	}
	return (free(key), ft_strdup(""));
}
