/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:47:06 by maroly            #+#    #+#             */
/*   Updated: 2022/02/22 15:05:48 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_global global;
	t_env *envi;

	envi = NULL;
	global.envi = &envi;
	(void)ac;
	(void)av;
	take_env(env, &envi); //leaks
	rl(&global);
	//write(1, "exit\n", 5);
	return (0);
}
