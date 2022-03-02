/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:47:06 by maroly            #+#    #+#             */
/*   Updated: 2022/03/02 13:15:06 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_global	global;
	t_env		*envi;

	if (ac != 1)
		return (1);
	envi = NULL;
	global = (t_global) {0};
	global.envi = &envi;
	take_env(env, &envi, av[0], &global);
	rl(&global);
	return (0);
}
