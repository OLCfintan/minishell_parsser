/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_rules.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:38:59 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/14 19:39:00 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	push(t_token **head, char *cmd)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->value = cmd;
	new_node->next = (*head);
	(*head) = new_node;
}

void	pop(t_token **head)
{
	t_token	*tmp;

	tmp = (*head);
	(*head) = (*head)->next;
	free(tmp);
}

void	remove_node(t_token **head, char *cmd)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = (*head);
	prev = NULL;
	if (tmp && tmp->value == cmd)
	{
		(*head) = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp && tmp->value != cmd)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free(tmp);
}
