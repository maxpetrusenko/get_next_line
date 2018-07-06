/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 19:26:28 by mpetruse          #+#    #+#             */
/*   Updated: 2018/07/06 14:33:37 by mpetruse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

static int	reader(const int fd, char **str)
{
	char	buf[BUFF_SIZE + 1];
	char	*tmp;
	int		i;

	if ((i = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[i] = '\0';
		tmp = *str;
		*str = ft_strjoin(tmp, buf);
		free(tmp);
	}
	return (i);
}

int			get_next_line(int const fd, char **line)
{
	static char *buf[4096];
	char		*end_line;
	int			i;

	if (fd < 0 || !line)
		return (-1);
	if (!buf[fd])
		buf[fd] = ft_strnew(1);
	while (!(end_line = ft_strchr(buf[fd], '\n')))
	{
		if ((i = reader(fd, &buf[fd])) < 0)
			return (-1);
		if (i == 0 && !end_line)
		{
			if (buf[fd][0] == '\0')
				return (0);
			*line = buf[fd];
			buf[fd] = NULL;
			return (1);
		}
	}
	*line = ft_strsub(buf[fd], 0, end_line - buf[fd]);
	free(buf[fd]);
	buf[fd] = ft_strdup(end_line + 1);
	return (1);
}
