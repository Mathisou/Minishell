/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:47:06 by maroly            #+#    #+#             */
/*   Updated: 2022/02/26 19:56:42 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_global global;
	t_env *envi;

	if (ac != 1)
		return (1); //
	envi = NULL;
	global.envi = &envi;
	take_env(env, &envi);
	rl(&global, av[0]);
	return (0);
}
