/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reddirections_pip.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:38:30 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/14 19:56:16 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "store.h"

// Function to initialize a redirection node

t_cmd	*handle_pipe(t_cmd *curr_cmd, char **env)
{
	curr_cmd->next = init_cmd(env);
	return (curr_cmd->next);
}

t_redir	*init_redirection(t_types type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->next = NULL;
	return (redir);
}

t_redir	*redir_last(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_redirection(t_cmd *cmd, t_types type, char *file)
{
	t_redir	*redir;
	t_redir	*last;

	redir = init_redirection(type, file);
	if (!cmd->redirections)
		cmd->redirections = redir;
	else
	{
		last = redir_last(cmd->redirections);
		last->next = redir;
	}
}
