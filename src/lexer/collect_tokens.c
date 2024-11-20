/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:38:43 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/20 09:20:01 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*lexer_collect_larrow(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	if (lexer->c == '<')
	{
		lexer_advance(lexer);
		value = ft_strdup("<<");
		return (init_token(value, HEREDOC));
	}
	value = ft_strdup("<");
	return (init_token(value, REDIR_IN));
}

t_token	*lexer_collect_rarrow(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	if (lexer->c == '>')
	{
		lexer_advance(lexer);
		value = ft_strdup(">>");
		return (init_token(value, REDIR_APPEND));
	}
	value = ft_strdup(">");
	return (init_token(value, REDIR_OUT));
}

t_token	*lexer_collect_cmd(t_lexer *lexer, char **env)
{
	char	*value;

	value = ft_strdup("");
	while (lexer->c != '\0')
	{
		check_if_expand(lexer, env, &value);
		if (check_if_quotes(lexer, env, &value) == 0)
			break ;
		if (lexer->c != '\'' && lexer->c != '\"')
		{
			if (!is_cmd(lexer->c) || lexer->c == 0)
				break ;
			value = ft_strjoin_char(value, lexer->c);
		}
		lexer_advance(lexer);
	}
	return (init_token(value, CMD));
}

t_token	*lexer_collect_squote(t_lexer *lexer, char **env)
{
	char	*value;

	value = ft_strdup("");
	while (lexer->c != '\0')
	{
		lexer_advance(lexer);
		if (lexer->c == '\'')
		{
			lexer_advance(lexer);
			if (check_if_quotes(lexer, env, &value) == 0)
				return (NULL);
			check_if_cmd(lexer, env, &value);
			return (init_token(value, CMD));
		}
		else
			value = ft_strjoin_char(value, lexer->c);
	}
	free(value);
	return (NULL);
}

t_token	*lexer_collect_dquote(t_lexer *lexer, char **env)
{
	char	*value;

	value = ft_strdup("");
	while (lexer->c != '\0')
	{
		lexer_advance(lexer);
		check_if_expand(lexer, env, &value);
		if (lexer->c == '\"')
		{
			lexer_advance(lexer);
			if (check_if_quotes(lexer, env, &value) == 0)
				return (NULL);
			check_if_cmd(lexer, env, &value);
			return (init_token(value, CMD));
		}
		else
			value = ft_strjoin_char(value, lexer->c);
	}
	free(value);
	return (NULL);
}
