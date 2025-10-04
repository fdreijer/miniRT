/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:08:19 by kali              #+#    #+#             */
/*   Updated: 2025/10/04 18:12:14 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
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

#endif