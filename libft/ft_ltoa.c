/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 17:09:33 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/30 17:07:16 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static char		*ft_negative(long int n, long int i)
{
	char	*nbr;

	nbr = (char *)malloc(sizeof(char) * (i + 1));
	nbr[i + 1] = '\0';
	while (i > 0)
	{
		nbr[i] = -(n % 10) + 48;
		n = n / 10;
		i--;
	}
	nbr[0] = '-';
	return (nbr);
}

static char		*ft_positive(long int n, long int i)
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

char			*ft_ltoa(long int n)
{
	long int		quotient;
	long int		i;

	quotient = n;
	i = 0;
	while (quotient >= 10 || quotient <= -10)
	{
		i++;
		quotient = quotient / 10;
	}
	if (n < 0)
	{
		i++;
		return (ft_negative(n, i));
	}
	return (ft_positive(n, i));
}
