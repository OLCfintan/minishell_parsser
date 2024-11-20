/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:37:55 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/20 09:27:01 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_cmd_dd(t_cmd *cmd, char **env)
{
	t_cmd	*hold;
	int		i;
	t_redir	*redirrection;

	(void)env;
	hold = cmd;
	while (hold)
	{
		i = 0;
		redirrection = hold->redirections;
		printf("the number of arguments is ---> %d\n", hold->ac);
		while (hold->av[i] != NULL)
			printf("the arguments is ---> %s\n", hold->av[i++]);
		while (redirrection != NULL)
		{
			printf("the file is -->%s     and    the type is --> %d\n",
				redirrection->file,
				redirrection->type);
			redirrection = redirrection->next;
		}
		hold = hold->next;
	}
}

void	minishell_loop(t_minishell *minishell, char **env)
{
	minishell->env = env;
	while (1)
	{
		minishell->line = readline(LIGHT_BLUE "<<👾>>[ -limbo- ]<<👾>>$ " RESET);
		add_history(minishell->line);
		minishell->lexer = init_lexer(minishell->line);
		if (ft_strcmp(minishell->line, "exit"))
		{
			minishell->cmd = NULL;
			break ;
		}
		minishell->cmd = parse_store_cmd(minishell->lexer, env);
		print_cmd_dd(minishell->cmd, env);
		minishell_exit(minishell);
	}
}

void	minishell_exit(t_minishell *minishell)
{
	if (minishell->cmd)
	{
		free_cmd_list(minishell->cmd);
		minishell->cmd = NULL;
	}
	if (minishell->line)
	{
		free(minishell->line);
		minishell->line = NULL;
	}
	if (minishell->lexer)
	{
		free(minishell->lexer);
		minishell->lexer = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	if (ac == 1)
	{
		(void)av;
		minishell_loop(&minishell, env);
		clear_history();
		minishell_exit(&minishell);
	}
	else
		printf("invalid use of $ minishell $ .\n");
	return (0);
}
