/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/14 15:09:38 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/03/07 13:13:30 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*begin;

	tmp = f(lst);
	begin = tmp;
	lst = lst->next;
	while (lst != NULL)
	{
		tmp->next = f(lst);
		lst = lst->next;
		tmp = tmp->next;
	}
	return (begin);
}
