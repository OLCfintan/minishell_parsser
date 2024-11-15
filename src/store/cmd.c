/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:38:18 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/14 19:38:19 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "store.h"

t_cmd	*init_cmd(char **env)
{
	t_cmd	*cmd;

	(void)env;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->ac = 0;
	cmd->av = malloc(sizeof(char *));
	cmd->av[0] = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	store_av(t_cmd *cmd, char *av)
{
	int	i;

	if (!av)
		return ;
	i = 0;
	while (cmd->av[i])
		i++;
	cmd->av = realloc(cmd->av, (i + 2) * sizeof(char *));
	cmd->av[i] = ft_strdup(av);
	cmd->av[i + 1] = NULL;
}
