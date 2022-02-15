/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:12:49 by maroly            #+#    #+#             */
/*   Updated: 2022/02/15 14:18:59 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void rl(char **env)
{
	char *line;

	while (1)
	{
		line = readline("$> ");
		add_history(line);
		printf("%s\n", findpath(line, env));
		free(line);
		rl_on_new_line();
	}
	//rl_clear_history(); //not recognized
}