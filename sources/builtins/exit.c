/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:44 by maroly            #+#    #+#             */
/*   Updated: 2022/02/21 14:55:48 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exit_b(t_parse *parse)
{
    free(parse->line);
	destroy_tab(parse->t);
    ft_putstr("exit\n"); // ecris 2 fois, mais quand on retire, ecris rien
    printf("test]n\n");
    exit(0); // a chaque cd -> un exit (creation d'autre process?)
}