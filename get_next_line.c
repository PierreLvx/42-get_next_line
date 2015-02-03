/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavaux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 17:23:59 by plavaux           #+#    #+#             */
/*   Updated: 2015/02/03 17:21:46 by plavaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		reader(int const fd, char *buffer, char **pos)
{
	int		status;
	char	*c;

	while (!(c = ft_strchr(pos[fd], '\n'))
		&& (status = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[status] = '\0';
		pos[fd] = ft_strjoin(pos[fd], buffer);
	}
	ft_strdel(&buffer);
	return (status == -1 || (!c && status == 0)) ? status : 1;
}

int				get_next_line(int const fd, char **line)
{
	int			status;
	char		*buffer;
	char		*tmp;
	static char	*pos[1];

	buffer = ft_strnew(BUFF_SIZE);
	if (fd < 0 || !line || !buffer)
		return (-1);
	if (!pos[fd])
		pos[fd] = ft_strnew(1);
	status = reader(fd, buffer, pos);
	if (status <= 0)
	{
		if (!status)
			*line = pos[fd];
		return (status);
	}
	*line = ft_strsub(pos[fd], 0, (ft_strchr(pos[fd], '\n') - pos[fd]));
	tmp = pos[fd];
	pos[fd] = ft_strdup(ft_strchr(tmp, '\n') + 1);
	ft_strdel(&tmp);
	return (1);
}
