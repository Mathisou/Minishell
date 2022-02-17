/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:12:58 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/17 15:45:41 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    error_exit(void* addr, char *str, char *to_free, char **free_tab)
{
    if (!addr)
    {
        if (to_free)
            free(to_free);
        if (free_tab)
            destroy_tab(free_tab);
        if (str)
            ft_putstr_fd(str, 2);
        //free();
        exit (1);
    }
}