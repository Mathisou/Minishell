/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:53:28 by maroly            #+#    #+#             */
/*   Updated: 2022/03/04 17:53:44 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_big_tab(char ***bt)
{
	int	i;

	i = -1;
	if (bt)
	{
		while (bt[++i])
			destroy_tab(bt[i]);
		free(bt);
	}
}

int	pid_del_list(t_pid **lst)
{
	t_pid	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free(*lst);
			*lst = tmp;
		}
	}
	return (0);
}
