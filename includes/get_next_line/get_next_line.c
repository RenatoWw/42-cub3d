/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:35:08 by dapinhei          #+#    #+#             */
/*   Updated: 2025/09/02 19:02:12 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_break_rest(char **rest)
{
	char	*temporary_rest;
	char	*start;
	char	*end;
	char	*line;

	temporary_rest = NULL;
	start = *rest;
	end = *rest;
	while (*end && *end != '\n')
		end++;
	if (*end != '\0')
	{
		temporary_rest = ft_strdup(end + 1);
		line = ft_substrp(start, start, (end - start) + 1);
	}
	else
	{
		temporary_rest = ft_strdup("");
		line = ft_substrp(start, start, (end - start));
	}
	free(*rest);
	*rest = temporary_rest;
	return (line);
}

void	ft_free_rest(char **rest)
{
	free(*rest);
	*rest = NULL;
}

static char	*ft_get_line(int fd, char **rest, char *buffer)
{
	int		bytes_read;
	char	*temporary_rest;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free_rest(rest), NULL);
		buffer[bytes_read] = '\0';
		temporary_rest = ft_strjoin(*rest, buffer);
		free(*rest);
		*rest = temporary_rest;
		if (ft_strchr(*rest, '\n'))
			return (ft_break_rest(rest));
	}
	if (bytes_read == 0 && *(*rest) != '\0')
	{
		temporary_rest = *rest;
		*rest = NULL;
		return (temporary_rest);
	}
	return (ft_free_rest(rest), NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (rest)
			ft_free_rest(&rest);
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!rest)
		rest = ft_strdup("");
	if (!rest)
		return (free(buffer), NULL);
	line = ft_get_line(fd, &rest, buffer);
	if (!line)
		return (free(buffer), NULL);
	return (free(buffer), line);
}
