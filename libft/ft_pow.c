/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 17:10:51 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/06/10 17:15:07 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_pow(int *current, int pow, int mult)
{
	*current += *current * mult;
	if (pow > 0)
		ft_pow(current, pow - 1, mult);
}
