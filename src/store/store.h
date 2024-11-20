/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:38:34 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/20 09:29:18 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STORE_H
# define STORE_H

# include "../../include/minishell.h"

void	add_redirection_cmd(t_cmd *cmd, t_types type, char *file);
void	parse_av_add(t_cmd *cmd, char *av);
void	execute_cmds(t_cmd *cmd_list, char **env);
void	free_cmd_list(t_cmd *cmd_list);
void	execute_single_cmd(t_cmd *cmd);

t_redir	*init_redirection_cmd(t_types type, char *file);

t_cmd	*parse_pipe_cmd(t_cmd *curr_cmd, char **env);
t_cmd	*init_cmd(char **env);

#endif
