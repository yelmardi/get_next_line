/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mard <yel-mard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:18:23 by yel-mard          #+#    #+#             */
/*   Updated: 2023/01/23 11:41:16 by yel-mard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_and_save(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	save = get_save(save);
	return (line);
}

char	*read_and_save(int fd, char *save)
{
	int		read_bytes;
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			{
				free(buff);
				return (NULL);
			}
		buff[read_bytes] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}
