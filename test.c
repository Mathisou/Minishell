/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:12:49 by maroly            #+#    #+#             */
/*   Updated: 2022/02/15 13:08:29 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*findpath(char *cmd, char **env);

int main(int ac, char **av, char **env)
{
	char *line;
	(void)ac, (void)av, (void)env;

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