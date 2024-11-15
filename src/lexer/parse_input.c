/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:39:03 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/15 02:20:59 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_cmd(t_cmd *cmd, char *str)
{
	store_av(cmd, str);
	cmd->ac++;
}

void	add_redir(t_cmd *cmd, t_lexer *lexer, char **env, t_types type)
{
	t_token	*tmp;

	tmp = lexer_get_next_token(lexer, env);
	add_redirection(cmd, type, tmp->value);
	free_token(tmp);
}

void	check_cmd(t_cmd **cmd_list, char **env)
{
	*cmd_list = init_cmd(env);
}

void	collect_cmd(t_cmd *cmd_list, t_lexer *lexer, t_token *token, char **env)
{
	t_cmd	*curr_cmd;

	curr_cmd = cmd_list;
	if (token->type == CMD)
		add_cmd(curr_cmd, token->value);
	else if (token->type == PIPE)
	{
		curr_cmd = handle_pipe(curr_cmd, env);
	}
	else if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_APPEND || token->type == HEREDOC)
		add_redir(curr_cmd, lexer, env, token->type);
}

t_cmd	*parse_input(t_lexer *lexer, char **env)
{
	t_cmd	*cmd_list;
	//t_cmd	*curr_cmd;
	t_token	*token;

	cmd_list = NULL;
	//curr_cmd = NULL;
	token = lexer_get_next_token(lexer, env);
	while (token->type != END)
	{
		if (!cmd_list)
			check_cmd(&cmd_list, env);
		collect_cmd(cmd_list, lexer, token, env);
		free_token(token);
		token = lexer_get_next_token(lexer, env);
	}
	free_token(token);
	return (cmd_list);
}
