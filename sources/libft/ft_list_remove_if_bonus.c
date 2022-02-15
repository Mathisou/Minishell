/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:42 by maroly            #+#    #+#             */
/*   Updated: 2021/10/19 13:31:29 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = *begin_list;
	while (tmp1 && cmp(tmp1->content, data_ref) == 0)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		free(tmp2);
	}
	while (tmp1 && tmp1->next)
	{
		if (cmp(tmp1->next->content, data_ref) == 0)
		{
			tmp2 = tmp1->next;
			tmp1->next = tmp1->next->next;
			free(tmp2);
		}
		if (tmp1->next)
			tmp1 = tmp1->next;
	}
}
