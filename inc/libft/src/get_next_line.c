/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:24:55 by fdreijer          #+#    #+#             */
/*   Updated: 2025/10/05 10:55:38 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 501
#endif

char	*fillbuffer(int fd, char *file, ssize_t	bytesread)
{
	char	*buffer;
	char	*temp;

	if (file == NULL)
		file = ft_calloc(1, 1);
	if (!file)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(file), NULL);
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (free(file), free(buffer), NULL);
		buffer[bytesread] = 0;
		temp = file;
		file = ft_strjoin(temp, buffer);
		if (!file)
			return (free(temp), free(buffer), NULL);
		free (temp);
		if (ft_strchr(file, '\n'))
			break ;
	}
	return (free(buffer), file);
}

char	*make_next_line(char *file)
{
	char	*line;
	int		i;

	i = 0;
	if (!file || file[0] == '\0')
		return (NULL);
	while (file[i] && file[i] != '\n')
		i++;
	if (file[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (file[i] && file[i] != '\n')
	{
		line[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
	{
		line[i] = file[i];
		i++;
	}
	return (line);
}

char	*file_next_line(char *file)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (!file[i] || (file[i] == '\n' && !file[i + 1]))
		return (free(file), NULL);
	i++;
	temp = ft_calloc(ft_strlen(&file[i]) + 1, sizeof(char));
	if (!temp)
		return (free(file), NULL);
	j = 0;
	while (file[i + j])
	{
		temp[j] = file[i + j];
		j++;
	}
	return (free(file), temp);
}

char	*get_next_line(int fd)
{
	static char	*file = NULL;
	char		*n_line;

	if (fd < 0)
	{
		free(file);
		file = NULL;
		return (NULL);
	}
	if (BUFFER_SIZE <= 0)
		return (NULL);
	file = fillbuffer(fd, file, 1);
	if (file == NULL)
		return (NULL);
	if (file[0] == '\0')
		return (get_next_line(-1));
	n_line = make_next_line(file);
	if (!n_line)
		return (get_next_line(-1));
	file = file_next_line(file);
	if (!n_line || n_line[0] == '\0')
		return (free(n_line), get_next_line(-1));
	return (n_line);
}
