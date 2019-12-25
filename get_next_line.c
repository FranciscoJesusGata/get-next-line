/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:04:00 by fgata-va          #+#    #+#             */
/*   Updated: 2019/12/23 12:11:04 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clean_line(char *save, char **line)
{
	int	i;
	char *tmp;

	if(save)
	{
		i = 0;
		while (save[i] != '\0' && save[i] != '\n')
			i++;
		if (i > 0)
		{	
			*line = ft_substr(save, 0, i);
			tmp = ft_substr(save, i + 1, ft_strlen(save));
			free(save);
			save = ft_strdup(tmp);
			free(tmp);
			return(save);
		}
		else
		{
			free(save);
			return(NULL);
		}
	}
	return (NULL);
}

int     	get_next_line(int fd, char **line)
{
	int		r;
	static char	*save[4096];
	char	buffer[BUFFER_SIZE + 1];
	int		i;
	char	*tmp;

	while((r = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[r] = '\0';
		i = 0;
		if(save[fd])
		{
			tmp = ft_strjoin(save[fd], buffer);
			free(save[fd]);
			save[fd] = ft_strdup(tmp);
			free(tmp);
		}
		else
			save[fd] = ft_strdup(buffer);
		while(buffer[i] != '\0')
		{
			if(buffer[i] == '\n')
				break;
			i++;
		}
	}
	save[fd] = ft_clean_line(save[fd], line);
	if(r <= 0 && !save[fd])
	{
		free(*line);
		return (r);
	}
	return (1);
}

