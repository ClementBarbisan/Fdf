/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:41:26 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/14 12:07:15 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static int	ft_parse(int i, const char *str)
{
	int	result;
	int	minus;

	result = 0;
	minus = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = 1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		if (i > 0)
			result = result * 10;
		result += str[i] - 48;
		i++;
	}
	if (minus == 1)
		result = result * -1;
	return (result);
}

int			ft_atoi(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t'
				|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
				|| str[i] == '\r')
		i++;
	return (ft_parse(i, str));
}
