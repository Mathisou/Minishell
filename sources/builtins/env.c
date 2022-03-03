/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:42 by maroly            #+#    #+#             */
/*   Updated: 2022/03/03 18:50:47 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_env **lst, t_global *global)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		ft_putstr(tmp->var);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	free_in_child(global);
	exit (EXIT_SUCCESS);
}
