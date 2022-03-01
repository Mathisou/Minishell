/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:47:06 by maroly            #+#    #+#             */
/*   Updated: 2022/03/01 18:08:17 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_global	global;
	t_env		*envi;

	(void)av;
	if (ac != 1)
		return (1);
	envi = NULL;
	global.envi = &envi;
	take_env(env, &envi);
	rl(&global);
	return (0);
}
