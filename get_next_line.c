/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:04:00 by fgata-va          #+#    #+#             */
/*   Updated: 2019/12/20 22:38:39 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_concat_free(char *s, char *buffer)
{
	char	*tmp;

	if(s)
    {
		tmp = ft_strjoin(s, buffer);
		free(s);
		s = ft_strdup(tmp);
		free(tmp);
	}
	else
    {
		s = ft_strdup(buffer);
	}
	return (s);
}

int			ft_line_end(char *buffer)
{
	int i;

	i = 0;
	while(buffer[i] != '\0')
	{
		if(buffer[i] == '\n')
			return (1);
		if(buffer[i + 1] == '\0')
			return(2);
		i++;
	}
	return (0);
}

char	*ft_clean_line(char *save, char **line)
{
	int	i;
	char *tmp;
	char last;

	if(save)
	{
		i = 0;
		while (save[i] != '\0' && save[i] != '\n')
			i++;
		*line = ft_substr(save, 0, i);
		tmp = ft_substr(save, i + 1, BUFFER_SIZE - i);
		free(save);
		save = ft_strdup(tmp);
		return(save);
	}
	return (NULL);
}

int     	get_next_line(int fd, char **line)
{
	int		r;
	static char	*save[4096];
	char	buffer[BUFFER_SIZE + 1];
	int		end;

	r = read(fd, buffer, BUFFER_SIZE);
	end = 0;
	/*if(save[fd])
		save[fd] = ft_clean_line(save[fd], line);*/
	while(end != 1 && r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r > 0)
		{
			buffer[r] = '\0';
			end = ft_line_end(buffer);
			end = 1;
		}
		save[fd] = ft_concat_free(save[fd], buffer);
	}
	save[fd] = ft_clean_line(save[fd], line);
	if(r <= 0 && !save[fd])
		return (r);
	if(ft_line_end(save[fd]) == 2)
		free(save[fd]);
	return (1);
}

