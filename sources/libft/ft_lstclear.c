/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:17 by maroly            #+#    #+#             */
/*   Updated: 2021/11/24 17:28:49 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp_lst;

	if (lst)
	{
		while (*lst)
		{
			tmp_lst = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = tmp_lst;
		}
	}
}
