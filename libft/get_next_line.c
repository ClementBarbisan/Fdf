/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/05 15:04:05 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/05/19 15:55:41 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <libft.h>
#include <get_next_line.h>

static char		*ft_ncatbuf(char *line, char *buf, int j)
{
	char		*tmp;

	tmp = NULL;
	if (line != NULL)
	{
		tmp = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
		tmp = ft_strcpy(tmp, line);
		free(line);
	}
	line = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + j + 1));
	if (tmp != NULL)
	{
		line = ft_strcpy(line, tmp);
		free(tmp);
		line = ft_strncat(line, buf, j);
	}
	else
		line = ft_strncpy(line, buf, j);
	return (line);
}

static char		*ft_searchbuf(char *buf, int *j, int ret)
{
	int			i;
	int			k;
	char		*line;

	k = 0;
	if (buf[*j] == '\n')
		(*j)++;
	i = *j;
	while (buf[*j] != '\n' && *j < ret)
		(*j)++;
	line = (char *)malloc(sizeof(char) * (*j - i + 1));
	while (i < *j)
	{
		line[k] = buf[i];
		k++;
		i++;
	}
	line[k] = '\0';
	return (line);
}

static t_buf	*ft_add_list(int fd, t_buf *list)
{
	t_buf	*node;

	node = (t_buf *)malloc(sizeof(t_buf));
	if (list == NULL)
	{
		node->begin = node;
		node->next = NULL;
	}
	else
	{
		node->begin = list->begin;
		list->next = node;
	}
	node->fd = fd;
	node->j = 0;
	node->ret = 0;
	return (node);
}

static t_buf	*ft_choose_list(int fd, t_buf *list)
{
	if (list && list->begin && list->fd >= 0)
	{
		list = list->begin;
		while (list->fd != fd && list->next != NULL)
			list = list->next;
	}
	else
		list = ft_add_list(fd, NULL);
	if (list->fd != fd && list->next == NULL)
		list = ft_add_list(fd, list);
	return (list);
}

int				get_next_line(int const fd, char **line)
{
	static t_buf	*list;

	if (fd < 0 || !line)
		return (-1);
	list = ft_choose_list(fd, list);
	*line = ft_searchbuf(list->buf, &list->j, list->ret);
	if (list->buf[list->j] == '\n')
		return (1);
	while (list->buf[list->j] != '\n'
			&& (list->ret = read(fd, list->buf, BUFF_SIZE)) > 0)
	{
		list->buf[list->ret] = '\0';
		list->j = 0;
		while (list->buf[list->j] != '\n' && list->j < list->ret)
			list->j++;
		*line = ft_ncatbuf(*line, list->buf, list->j);
	}
	if (list->ret == -1)
		return (-1);
	if (list->ret > 0 || *line[0] != '\0')
		return (1);
	return (0);
}
