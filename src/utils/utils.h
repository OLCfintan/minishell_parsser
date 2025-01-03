/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:35:32 by oel-mouk          #+#    #+#             */
/*   Updated: 2024/11/20 09:13:33 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

/* ===== Macros ===== */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

int		ft_strcmp(const char *s1, const char *s2);
int		is_cmd(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isprint(int c);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char *stash, char *buff);
char	*ft_strrchr(const char s[], int c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
int		ft_iswp(int c);

#endif
