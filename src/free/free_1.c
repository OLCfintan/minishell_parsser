/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:39:15 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/15 02:11:08 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(t_token *token)
{
	if (token->value)
	{
		free(token->value);
	}
	free(token);
	token = NULL;
}

void	free_av(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->av[i])
		free(cmd->av[i++]);
	free(cmd->av);
	cmd->av = NULL;
}

t_redir	*free_redir(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	free(redir->file);
	redir = redir->next;
	free(temp);
	temp = NULL;
	return (redir);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	t_redir	*redir;

	current = NULL;
	while (cmd_list)
	{
		current = cmd_list;
		if (cmd_list->av)
			free_av(cmd_list);
		redir = cmd_list->redirections;
		while (redir)
			redir = free_redir(redir);
		cmd_list = cmd_list->next;
		free(current);
	}
}
