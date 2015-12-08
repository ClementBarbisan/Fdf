/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 15:17:51 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/06/03 17:05:38 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char	*ft_ftoa(float f)
{
	int		before;
	float	after;
	int		tmp;
	char	*tmps;
	char	*result;

	before = f;
	after = f - before;
	tmp = after;
	while (after - tmp != 0)
	{
		after = after / 10;
		tmp = after;
	}
	result = ft_itoa(before);
	tmps = ft_strjoin(result, ".\0");
	free(result);
	result = ft_strjoin(tmps, ft_itoa(tmp));
	return (result);
}
