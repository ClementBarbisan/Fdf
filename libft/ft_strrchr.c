/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 17:51:56 by cbarbisa          #+#    #+#             */
/*   Updated: 2013/12/13 11:45:51 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strrchr(const char *str, int c)
{
	char	*result;
	int		i;

	result = (char *)str;
	i = ft_strlen(result);
	while (i >= 0)
	{
		if (result[i] == c)
			return (&(result[i]));
		--i;
	}
	return (NULL);
}
