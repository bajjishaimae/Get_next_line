/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:27 by cbajji            #+#    #+#             */
/*   Updated: 2023/12/23 14:06:54 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_join_free(char *save, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(save, buffer);
	free(save);
	return (temp);
}

char	*ft_rest(char *save)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	rest = ft_calloc((ft_strlen(save) - i + 1), sizeof(char));
	if (!rest)
	{
		free(rest);
		return (NULL);
	}
	i++;
	j = 0;
	while (save[i])
		rest[j++] = save[i++];
	free(save);
	return (rest);
}

char	*ft_line(char *save)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		line = ft_calloc(i + 2, sizeof(char));
	else
		line = ft_calloc(i + 1, sizeof(char));
	if (!line)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (save[i] && save[i] != '\n')
		line[j++] = save[i++];
	if (save[i] && save[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_manip(int fd, char *save)
{
	char	*buffer;
	int		nb;

	if (!save)
		save = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	nb = 1;
	while (nb > 0)
	{
		nb = read(fd, buffer, BUFFER_SIZE);
		if (nb == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[nb] = '\0';
		save = ft_join_free(save, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd > OPEN_MAX)
		return (NULL);
	save[fd] = ft_manip(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_line(save[fd]);
	save[fd] = ft_rest(save[fd]);
	return (line);
}
