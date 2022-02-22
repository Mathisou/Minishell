/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:44 by maroly            #+#    #+#             */
/*   Updated: 2022/02/22 10:43:59 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exit_b(t_global *global)
{
    free(global->parse->line);
	destroy_tab(global->parse->t);
    del_list(global->envi);
	free(global->parse);
    ft_putstr("exit\n");
    exit(0); // a chaque cd -> un exit (creation d'autre process?)
}