/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 17:09:33 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/14 11:51:49 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

void		ft_putnbr(int n)
{
	char	*nbr;

	nbr = ft_itoa(n);
	ft_putstr(nbr);
	free(nbr);
	nbr = NULL;
}
