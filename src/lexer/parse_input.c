/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:39:03 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/14 19:39:04 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_redir(t_cmd *cmd, t_lexer *lexer, char **env, t_types type)
{
	t_token	*tmp;

	tmp = lexer_get_next_token(lexer, env);
	add_redirection(cmd, type, tmp->value);
	free_token(tmp);
}

void	handle_initialization(t_cmd **cmd_list, t_cmd **curr_cmd, char **env)
{
	if (!(*cmd_list))
	{
		*cmd_list = init_cmd(env);
		*curr_cmd = *cmd_list;
	}
}

void	process_token(t_token *token, t_cmd **curr_cmd, t_lexer *lexer,
		char **env)
{
	if (token->type == CMD)
	{
		store_av(*curr_cmd, token->value);
		(*curr_cmd)->ac++;
	}
	else if (token->type == PIPE)
		*curr_cmd = handle_pipe(*curr_cmd, env);
	else if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_APPEND || token->type == HEREDOC)
		add_redir(*curr_cmd, lexer, env, token->type);
}

t_cmd	*parse_input(t_lexer *lexer, char **env)
{
	t_token	*token;
	t_cmd	*cmd_list;
	t_cmd	*curr_cmd;

	cmd_list = NULL;
	curr_cmd = NULL;
	token = lexer_get_next_token(lexer, env);
	while (token->type != END)
	{
		handle_initialization(&cmd_list, &curr_cmd, env);
		process_token(token, &curr_cmd, lexer, env);
		free_token(token);
		token = lexer_get_next_token(lexer, env);
	}
	free_token(token);
	return (cmd_list);
}
