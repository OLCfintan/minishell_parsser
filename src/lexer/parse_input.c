/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:39:03 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/17 02:49:14 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_redir(t_cmd *cmd, t_token *token, int ttp)
{
	if (token->type == CMD)
		add_redirection(cmd, ttp, token->value);
}

void	handle_initialization(t_cmd **cmd_list, t_cmd **curr_cmd, char **env)
{
	if (!(*cmd_list))
	{
		*cmd_list = init_cmd(env);
		*curr_cmd = *cmd_list;
	}
}

void	process_token(t_token *token, int prev_type, t_cmd **curr_cmd, char **env)
{
	if (token->type == PIPE)
		*curr_cmd = handle_pipe(*curr_cmd, env);
	else if ((prev_type >= 2 && prev_type <= 5) && token->type == CMD)
		add_redir(*curr_cmd, token, prev_type);
	else if (token->type == CMD)
	{
		store_av(*curr_cmd, token->value);
		(*curr_cmd)->ac++;
	}
}

int	token_parss(t_token *token, int prev, int wr)
{
	prev += 2 * (token->type == PIPE && prev == -1);
	if (prev == 1 && ((int)token->type == PIPE || token->type == END))
	{
		if(wr == 1)
			printf("invalid use of pip \n");
		return (-1);
	}
	if ((prev >= 2 && prev <= 5) && (((int)token->type >= 2
				&& (int)token->type <= 5) || (int)token->type == PIPE
			|| (int)token->type == END))
	{
		if(wr == 1)
			printf("invalid use of redirections \n");
		return (-1);
	}
	return (1);
}

t_cmd	*parse_input(t_lexer *lexer, char **env)
{
	int		prev;
	t_token	*token;
	t_cmd	*cmd_list;
	t_cmd	*curr_cmd;

	cmd_list = NULL;
	curr_cmd = NULL;
	token = lexer_get_next_token(lexer, env);
	prev = 0;
	while (token_parss(token, prev, 1) == 1 && token->type != END)
	{
		handle_initialization(&cmd_list, &curr_cmd, env);
		process_token(token, prev, &curr_cmd, env);
		prev = token->type;
		free_token(token);
		token = lexer_get_next_token(lexer, env);
	}
	if (token_parss(token, prev, 0) == -1 && cmd_list)
		return (free_token(token), free_cmd_list(cmd_list), NULL);
	free_token(token);
	return (cmd_list);
}

