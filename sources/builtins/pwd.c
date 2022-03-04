/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:47 by maroly            #+#    #+#             */
/*   Updated: 2022/03/04 13:58:42 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_global *global)
{
	char	*pwd;

	pwd = getcwd(NULL, 4096 + 1);
	ft_putstr(pwd);
	free(pwd);
	write(1, "\n", 1);
	free_in_child(global);
	exit (EXIT_SUCCESS);
}
