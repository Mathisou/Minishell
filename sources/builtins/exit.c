/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:44 by maroly            #+#    #+#             */
/*   Updated: 2022/03/04 14:14:26 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_b(t_global *global, int sign)
{
	if (sign == 1 && count_triple_tab(global->parse->bt) == 1)
		ft_putstr("exit\n");
	free_in_child(global);
	exit(EXIT_SUCCESS);
}
