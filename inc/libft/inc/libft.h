/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:08:19 by kali              #+#    #+#             */
/*   Updated: 2025/10/05 10:56:11 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
int			ft_atoi(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isspace(char c);
char		*ft_itoa(int n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_realloc(void *oldptr, int oldsize, int newsize);
char		**ft_split(char const *s, char c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(char *str, int n);
int			ft_min(int a, int b);
char		*get_next_line(int fd);
char		*ft_strchr(const char *s, int c);
int			ft_isdigit(char c);
double		ft_atof(char *s);
char		**split_space(char *str);
void 		free_split(char **split);

#endif