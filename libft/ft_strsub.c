/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 14:59:07 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/18 19:47:21 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*tmp;

	i = 0;
	if ((int)len < 0)
		return (NULL);
	tmp = ft_memalloc(len + 1);
	if (!s || s[0] == '\0')
		return (NULL);
	while (i < len)
	{
		tmp[i] = s[start + i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
