/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 17:09:33 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/06/03 17:05:05 by cbarbisa         ###   ########.fr       */
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
		nbr[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (nbr);
}

char			*ft_lutoa(unsigned long n)
{
	unsigned long		quotient;
	long				i;

	quotient = n;
	i = 0;
	while (quotient >= 10)
	{
		i++;
		quotient = quotient / 10;
	}
	return (ft_positive(n, i));
}
