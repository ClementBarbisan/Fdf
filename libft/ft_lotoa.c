/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lotoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 17:09:33 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/05/04 21:42:36 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static char		*ft_positive(unsigned long n, long i)
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

char			*ft_lotoa(unsigned long n)
{
	unsigned long	quotient;
	long			i;

	quotient = n;
	i = 0;
	while (quotient >= 8)
	{
		i++;
		quotient = quotient / 8;
	}
	return (ft_positive(n, i));
}
