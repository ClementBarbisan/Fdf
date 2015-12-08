/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/04 13:40:39 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/03/10 11:32:10 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 4096

typedef struct s_buf	t_buf;

struct					s_buf
{
	int					ret;
	int					fd;
	int					j;
	char				buf[BUFF_SIZE];
	t_buf				*next;
	t_buf				*begin;
};

int						get_next_line(int const fd, char **line);

#endif
