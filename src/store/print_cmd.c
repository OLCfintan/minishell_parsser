/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:38:27 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/14 19:38:28 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "store.h"

void	print_cmd(t_cmd *cmd_list)
{
	t_redir	*tmp;
	t_cmd	*temp;
	int		i;

	if (!cmd_list)
		return ;
	temp = cmd_list;
	tmp = temp->redirections;
	while (temp)
	{
		i = 0;
		while (temp->av[i] != NULL)
		{
			printf("the number of arguments is ---->%d\n", temp->ac);
			printf("argumnet is -->%s\n", temp->av[i++]);
		}
		if (tmp != NULL)
		{
			while (tmp)
			{
				printf("file is ---> %s  and type is %d\n", tmp->file,
					(int)tmp->type);
				tmp = tmp->next;
			}
		}
		temp = temp->next;
	}
}
