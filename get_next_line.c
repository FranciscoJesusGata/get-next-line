/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:04:00 by fgata-va          #+#    #+#             */
/*   Updated: 2019/12/17 18:38:01 by fgata-va         ###   ########.fr       */
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
		i++;
	}
	return (0);
}

char	*ft_clean_line(char *s, char **save)
{
	int	i;
	char *tmp;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	tmp = ft_substr(s, 0, i);
	*save = ft_substr(s, i, BUFFER_SIZE - i);
	free(s);
	s = ft_strdup(tmp);
	return (s);
}

int     	get_next_line(int fd, char **line)
{
	int		r;
	static char	*save[4096];
	char	buffer[BUFFER_SIZE + 1];
	char	*s;
	int		end;

	if(save[fd])
		s = ft_strdup(save[fd]);
	r = 1;
	end = 0;
	while(end != 1 && r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r > 0)
		{
			buffer[BUFFER_SIZE] = '\0';
			end = ft_line_end(buffer);
			end = 1;
		}
		s = ft_concat_free(s, buffer);
	}
	if(r <= 0)
		return (r);
	s = ft_clean_line(s, &save[fd]);
	*line = ft_strdup(s);
	free(s);
	return (1);
}

