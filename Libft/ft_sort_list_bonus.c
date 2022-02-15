/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_list_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:17:45 by maroly            #+#    #+#             */
/*   Updated: 2021/10/19 13:18:43 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_sort_list(t_list *lst, int (*cmp)())
{
	t_list	*tmp_l;
	t_list	*temp2;
	void	*swap;

	tmp_l = lst;
	while (tmp_l != NULL)
	{
		temp2 = tmp_l->next;
		while (temp2 != NULL)
		{
			if (cmp(tmp_l->content, temp2->content) == 0)
			{
				swap = tmp_l->content;
				tmp_l->content = temp2->content;
				temp2->content = swap;
			}
			temp2 = temp2->next;
		}
		tmp_l = tmp_l->next;
	}
}
