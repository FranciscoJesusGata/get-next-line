/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:04:00 by fgata-va          #+#    #+#             */
/*   Updated: 2020/01/09 19:05:27 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clean_line(char *save, char **line, int r)
{
	int	i;
	int j;
	char *tmp;

	if(save)
	{
		i = 0;
		j = 1;
		while (save[i] != '\n')
		{
			if(save[i] == '\0')
			{
				j = 0;
				if (r == 0)
				{
					*line = save;
					save = NULL;
				}
				break;
			}
			i++;
		}
		if (i > 0 && j > 0)
		{	
			*line = ft_substr(save, 0, i);
			tmp = ft_substr(save, i + 1, ft_strlen(save));
			free(save);
			save = ft_strdup(tmp);
			free(tmp);
			return(save);
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
		if(save[fd])
		{
			tmp = ft_strjoin(save[fd], buffer);
			free(save[fd]);
			save[fd] = ft_strdup(tmp);
			free(tmp);
		}
		else
			save[fd] = ft_strdup(buffer);
		i = 0;
		while(i < r && save[fd][i] != '\n')
		{
			if(save[fd][i] == '\0')
				return(0);
			i++;
		}
		if(save[fd][i] == '\n')
		{
			free(save[fd]);
			break;
		}
	}
	save[fd] = ft_clean_line(save[fd], line, r);
	if(r <= 0 && !save[fd])
	{
		*line = ft_strdup("");
		return (r);
	}
	return (1);
}

