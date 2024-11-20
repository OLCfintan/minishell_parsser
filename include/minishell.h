/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:32:47 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/20 09:29:18 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/utils/utils.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define LIGHT_BLUE "\x1B[1;34m"
# define RESET "\x1B[0m"

typedef enum s_types
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	END,
}					t_types;

typedef struct s_lexer
{
	char			*line;
	size_t			line_len;
	char			c;
	size_t			i;
}					t_lexer;

typedef struct s_token
{
	char			*value;
	t_types			type;
	struct s_token	*next;
}					t_token;

typedef struct s_parser
{
	t_token			*token;
	struct s_parser	*curr;
	struct s_parser	*next;
}					t_parser;

typedef struct s_redir
{
	char			*file;
	t_types			type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	int				ac;
	int				exit;
	char			**av;

	t_redir			*redirections;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_minishell
{
	char			*line;
	char			**env;
	t_lexer			*lexer;
	t_cmd			*cmd;
}					t_minishell;

void				minishell_loop(t_minishell *minishell, char **env);
void				minishell_exit(t_minishell *minishell);

t_token				*init_token(char *value, t_types type);
void				print_tokens(t_lexer *lexer, char **env);

t_cmd				*parse_store_cmd(t_lexer *lexer, char **env);

t_lexer				*init_lexer(char *line);
t_token				*lexer_collect_heredoc(t_lexer *lexer);
void				lexer_advance(t_lexer *lexer);
t_token				*lexer_advance_with(t_token *token, t_lexer *lexer);
char				*lexer_get_env_value(t_lexer *lexer, char **env);
t_token				*lexer_collect_cmd(t_lexer *lexer, char **env);
t_token				*lexer_collect_squote(t_lexer *lexer, char **env);
t_token				*lexer_collect_dquote(t_lexer *lexer, char **env);
t_token				*lexer_collect_rarrow(t_lexer *lexer);
t_token				*lexer_collect_larrow(t_lexer *lexer);

t_token				*lexer_get_next_token(t_lexer *lexer, char **env);
void				check_if_expand(t_lexer *lexer, char **env, char **value);
int					check_if_quotes(t_lexer *lexer, char **env, char **value);
void				check_if_cmd(t_lexer *lexer, char **env, char **value);

char				*ft_strjoin_char(char *s1, char c);

void				add_redirection_cmd(t_cmd *cmd, t_types type, char *file);
void				parse_av_add(t_cmd *cmd, char *av);
void				execute_cmds(t_cmd *cmd_list, char **env);
void				free_cmd_list(t_cmd *cmd_list);
void				execute_single_cmd(t_cmd *cmd);
void				print_cmd(t_cmd *cmd_list);
t_redir				*init_redirection_cmd(t_types type, char *file);
t_cmd				*parse_pipe_cmd(t_cmd *curr_cmd, char **env);
t_cmd				*init_cmd(char **env);

void				free_cmd_list(t_cmd *cmd_list);

void				free_token(t_token *token);

#endif
