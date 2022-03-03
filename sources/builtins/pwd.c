/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:47 by maroly            #+#    #+#             */
/*   Updated: 2022/03/03 18:55:48 by hkovac           ###   ########.fr       */
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
