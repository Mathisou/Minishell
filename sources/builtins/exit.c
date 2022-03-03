/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:44 by maroly            #+#    #+#             */
/*   Updated: 2022/03/03 19:31:17 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_b(t_global *global)
{
	if (count_triple_tab(global->parse->bt) == 1)
		ft_putstr("exit\n");
	free_in_child(global);
	exit(EXIT_SUCCESS);
}
