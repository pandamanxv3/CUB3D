/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:29:55 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/03 15:50:06 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_checkendofline(char *buffer_save)
{
	int	i;

	i = 0;
	if (!buffer_save)
		return (1);
	while (buffer_save[i])
	{
		if (buffer_save[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_print_line(char *buffer_save)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer_save)
		return (NULL);
	while (buffer_save[i] && buffer_save[i] != '\n')
		i++;
	line = ft_substr(buffer_save, 0, i + 1);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_get_buffer_save(char *buffer_save)
{
	int		i;
	int		strlen;
	char	*new_buffer_save;

	new_buffer_save = NULL;
	i = 0;
	strlen = ft_strlen(buffer_save);
	if (!buffer_save)
		return (NULL);
	while (buffer_save[i])
	{
		if (buffer_save[i] == '\n' && buffer_save[i + 1] != '\0')
		{
			i += 1;
			new_buffer_save = ft_substr(buffer_save, i, (strlen - i) + 1);
			break ;
		}
		else if (buffer_save[i + 1] == '\0')
			buffer_save[0] = '\0';
		i++;
	}
	free (buffer_save);
	return (new_buffer_save);
}

char	*ft_read(int fd, char *buffer_read)
{
	int			ret;
	char		*line;
	static char	*buffer_save = NULL;

	ret = 1;
	while (ret > 0)
	{
		if (ft_checkendofline(buffer_save) == 0)
			break ;
		ret = read(fd, buffer_read, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buffer_read[ret] = '\0';
		if (buffer_save == NULL)
			buffer_save = ft_strdup(buffer_read);
		else
			buffer_save = ft_strjoingnl(buffer_save, buffer_read);
	}
	line = ft_print_line(buffer_save);
	buffer_save = ft_get_buffer_save(buffer_save);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		buffer_read[BUFFER_SIZE + 1];

	if (fd > 1024 || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read(fd, buffer_read);
	return (line);
}
