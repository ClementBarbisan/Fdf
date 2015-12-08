/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 17:09:33 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/06/03 17:04:41 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <libft.h>

static char	*ft_positive(int n, int i)
{
	char	*nbr;

	if (n < 0)
		n = -n;
	nbr = (char *)malloc(sizeof(char) * (i + 1));
	nbr[i + 1] = '\0';
	while (i >= 0)
	{
		if (n % 16 < 10 && n % 16 >= 0)
			nbr[i] = (n % 16) + 48;
		else
			nbr[i] = (n % 16) + 87;
		n = n / 16;
		i--;
	}
	return (nbr);
}

static char	*ft_negative(char *result, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = (char *)malloc(sizeof(char) * 9);
	while (j < 8)
	{
		tmp[j] = 'f';
		j++;
	}
	tmp[j] = '\0';
	j = 0;
	while (i >= 0)
	{
		if (result[j] == '0')
			tmp[7 - i] = '0';
		else if (result[j] <= 54 || result[j] >= 97)
			tmp[7 - i] = tmp[7 - i] - (result[j] - 49);
		else
			tmp[7 - i] = tmp[7 - i] - (result[j] - 9);
		i--;
		j++;
	}
	return (tmp);
}

char		*ft_htoa(int n)
{
	int		quotient;
	int		i;
	char	*result;

	quotient = n;
	i = 0;
	while (quotient >= 16 || quotient <= -16)
	{
		i++;
		quotient = quotient / 16;
	}
	result = ft_positive(n, i);
	if (n < 0)
		return (ft_negative(result, i));
	return (result);
}
