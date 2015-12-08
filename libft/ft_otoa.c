/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 17:09:33 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/05/01 11:32:24 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static char		*ft_positive(unsigned int n, int i)
{
	char	*nbr;

	nbr = (char *)malloc(sizeof(char) * (i + 1));
	nbr[i + 1] = '\0';
	while (i >= 0)
	{
		nbr[i] = (n % 8) + 48;
		n = n / 8;
		i--;
	}
	return (nbr);
}

char			*ft_otoa(unsigned int n)
{
	unsigned int	quotient;
	int				i;

	quotient = n;
	i = 0;
	while (quotient >= 8)
	{
		i++;
		quotient = quotient / 8;
	}
	return (ft_positive(n, i));
}
