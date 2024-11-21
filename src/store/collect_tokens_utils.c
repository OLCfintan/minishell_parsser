/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_tokens_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:35:38 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/21 10:54:41 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_cmd(t_lexer *lexer, char **env, char **value)
{
	t_token	*token;

	if (ft_isprint(lexer->c))
	{
		token = lexer_collect_cmd(lexer, env);
		if (token != NULL)
		{
			*value = ft_strjoin(*value, token->value);
			return (free(token), 1);
		}
		return (0);
	}
	return (-1);
}

int	if_qts(t_lexer *lexer, char **env, char **value, int hdc)
{
	t_token	*token;
	int		i;

	if (lexer->c == '\'')
	{
		token = lexer_collect_squote(lexer, env);
		i = (lexer->c == '\'');
		if (lexer->c == '\'')
			lexer_advance(lexer);
		if (token)
			*value = ft_strjoin(*value, token->value);
		return (free(token), i * (if_qts(lexer, env, value, hdc) != 0));
	}
	else if (lexer->c == '\"')
	{
		token = lexer_collect_dquote(lexer, env, hdc);
		i = (lexer->c == '\"');
		if (lexer->c == '\"')
			lexer_advance(lexer);
		if (token)
			*value = ft_strjoin(*value, token->value);
		return (free(token), i * (if_qts(lexer, env, value, hdc) != 0));
	}
	return (-1);
}

void	if_expand(t_lexer *lexer, char **env, char **value)
{
	while (lexer->c == '$')
	{
		lexer_advance(lexer);
		if (lexer->c != 0 && lexer->c != '$' && !ft_iswp(lexer->c))
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

t_token	*lexer_collect_heredoc(t_lexer *lexer, char **env)
{
	char	*value;

	value = ft_strdup("");
	while (ft_iswp(lexer->c))
		lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != '<')
	{
		if ((if_qts(lexer, env, &value, 1) == 0))
			return (free(value), init_token(ft_strdup("khssk\tctrl\n"), CMD));
		else
			value = ft_strjoin_char(value, lexer->c);
		lexer_advance(lexer);
		if (lexer->c == 32 || lexer->c == 0)
			return (init_token(value, CMD));
	}
	return (init_token(value, END));
}
