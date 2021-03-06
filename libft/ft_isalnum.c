/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:28:24 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/01/02 14:57:15 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57)
			|| (c >= 65 && c <= 90)
			|| (c >= 97 && c <= 122))
		return (1);
	return (0);
}
