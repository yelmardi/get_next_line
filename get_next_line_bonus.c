/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mard <yel-mard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:47:06 by yel-mard          #+#    #+#             */
/*   Updated: 2023/01/24 18:47:06 by yel-mard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[256];

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (0);
	save[fd] = read_and_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_get_line(save[fd]);
	save[fd] = get_save(save[fd]);
	return (line);
}

char	*read_and_save(int fd, char *save)
{
	char	*buff;
	int		bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(save, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(save);
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*ft_get_line(char *save)
{
	int		i;
	char	*tab;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	tab = (char *)malloc(sizeof(char) * (i + 2));
	if (!tab)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		tab[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		tab[i] = save[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*get_save(char *save)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	tab = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!tab)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		tab[j++] = save[i++];
	tab[j] = '\0';
	free(save);
	return (tab);
}
