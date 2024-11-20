/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_tokens_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:35:38 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/20 09:33:42 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_if_cmd(t_lexer *lexer, char **env, char **value)
{
	t_token	*token;

	if (ft_isprint(lexer->c))
	{
		token = lexer_collect_cmd(lexer, env);
		*value = ft_strjoin(*value, token->value);
		free(token);
	}
}

int	check_if_quotes(t_lexer *lexer, char **env, char **value)
{
	t_token	*token;
	int		i;

	if (lexer->c == '\'')
	{
		token = lexer_collect_squote(lexer, env);
		i = ft_strlen(*value);
		if (token)
			*value = ft_strjoin(*value, token->value);
		free(token);
		return (!(i == (int)ft_strlen(*value)));
	}
	else if (lexer->c == '\"')
	{
		token = lexer_collect_dquote(lexer, env);
		i = ft_strlen(*value);
		if (token)
			*value = ft_strjoin(*value, token->value);
		free(token);
		return (!(i == (int)ft_strlen(*value)));
	}
	return (-1);
}

void	check_if_expand(t_lexer *lexer, char **env, char **value)
{
	while (lexer->c == '$')
	{
		lexer_advance(lexer);
		if (lexer->c != 0 && lexer->c != '$')
		{
			if (lexer->c >= 48 && lexer->c <= 57)
			{
				while (lexer->c != 0 && lexer->c >= 48 && lexer->c <= 57)
					lexer_advance(lexer);
				*value = ft_strjoin(*value, ft_strdup(""));
			}
			else
				*value = ft_strjoin(*value, lexer_get_env_value(lexer, env));
		}
		else
		{
			if (lexer->c == '$')
			{
				lexer_advance(lexer);
				*value = ft_strjoin(*value, ft_strdup("$"));
			}
			*value = ft_strjoin(*value, ft_strdup("$"));
		}
	}
}

t_token	*lexer_collect_heredoc(t_lexer *lexer)
{
	char	*value;

	value = ft_strdup("");
	while (lexer->c == 32 || lexer->c == '\t')
		lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != '<')
	{
		if (lexer->c != '\'' && lexer->c != '\"')
			value = ft_strjoin_char(value, lexer->c);
		lexer_advance(lexer);
		if (lexer->c == 32 || lexer->c == 0)
			return (init_token(value, CMD));
	}
	return (init_token(value, END));
}
