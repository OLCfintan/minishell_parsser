/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:39:03 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/20 09:33:06 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_redir_add(t_cmd *cmd, t_token *token, int ttp)
{
	if (token->type == CMD)
		add_redirection_cmd(cmd, ttp, token->value);
}

void	parse_creat_cmd(t_cmd **cmd_list, t_cmd **curr_cmd, char **env)
{
	if (!(*cmd_list))
	{
		*cmd_list = init_cmd(env);
		*curr_cmd = *cmd_list;
	}
}

void	parse_token_add(t_token *token, int prev_type, t_cmd **curr_cmd,
		char **env)
{
	if (prev_type == 5)
		parse_redir_add(*curr_cmd, token, prev_type);
	if (token->type == PIPE)
		*curr_cmd = parse_pipe_cmd(*curr_cmd, env);
	else if ((prev_type >= 2 && prev_type < 5) && token->type == CMD)
		parse_redir_add(*curr_cmd, token, prev_type);
	else if (token->type == CMD)
	{
		parse_av_add(*curr_cmd, token->value);
		if (ft_strlen(token->value) == 0)
			return ;
		(*curr_cmd)->ac++;
	}
}

int	parse_err_token(t_token *token, int prev, int wr)
{
	if (prev != -2 && ft_strlen(token->value) == 0 && token->type != END)
	{
		if (wr == 1)
			printf("invalid use of quotes\n");
		return (-1);
	}
	prev += (prev == -2);
	prev += 2 * (token->type == PIPE && prev == -1);
	if ((prev >= 2 && prev <= 5) && (((int)token->type >= 2
				&& (int)token->type <= 5) || (int)token->type == PIPE
			|| (int)token->type == END))
	{
		if (wr == 1)
			printf("invalid use of redirections \n");
		return (-1);
	}
	if (prev == 1 && ((int)token->type == PIPE || token->type == END))
	{
		if (wr == 1)
			printf("invalid use of pip \n");
		return (-1);
	}
	return (1);
}

t_cmd	*parse_store_cmd(t_lexer *lexer, char **env)
{
	int		prev;
	t_token	*token;
	t_cmd	*cmd_list;
	t_cmd	*curr_cmd;

	cmd_list = NULL;
	curr_cmd = NULL;
	prev = -1 - (lexer->line[lexer->i] == '$');
	token = lexer_get_next_token(lexer, env);
	while (parse_err_token(token, prev, 1) == 1 && token->type != END)
	{
		parse_creat_cmd(&cmd_list, &curr_cmd, env);
		parse_token_add(token, prev, &curr_cmd, env);
		prev = token->type * (ft_strlen(token->value) != 0);
		free_token(token);
		if (prev == 5)
			token = lexer_collect_heredoc(lexer);
		else
			token = lexer_get_next_token(lexer, env);
		prev -= 2 * (ft_strlen(token->value) == 0);
	}
	if (parse_err_token(token, prev, 0) == -1 && cmd_list)
		return (free_token(token), free_cmd_list(cmd_list), NULL);
	free_token(token);
	return (cmd_list);
}
