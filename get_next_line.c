/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:04:00 by fgata-va          #+#    #+#             */
/*   Updated: 2019/12/16 17:00:31 by fgata-va         ###   ########.fr       */
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

char	*ft_clean_line(char *s)
{
	int	i;
	char *tmp;

	i = 0;
	while (s[i] != '\0' && (s[i] != '\n' || s[i] != '\0'))
		i++;
	tmp = ft_substr(s, 0, i);
	free(s);
	s = ft_strdup(tmp);
	return (s);
}

int     	get_next_line(int fd, char **line)
{
	int		r;
	int		i;
	int		final;
	char	buffer[BUFFER_SIZE + 1];
	char	*s;

	final = 0;
	r = 1;
	while(r != 0 && final == 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';
		i = 0;
		while(buffer[i] != '\0')
		{
			if(buffer[i] != '\n')
				final = 1;
			i++;
		}
		s = ft_concat_free(s, buffer);
	}
	if(r == 0)
		return (0);
	if (r < 0)
		return (-1);
	*line = ft_strdup(ft_clean_line(s));
	free(s);
	return (1);
}

