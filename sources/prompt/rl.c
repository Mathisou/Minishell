/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:12:49 by maroly            #+#    #+#             */
/*   Updated: 2022/02/16 13:21:22 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void rl(char **env)
{
	char				*line;
	struct sigaction	sa;
	char				*cmd;

	env++;
	sa.sa_handler = handler;
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		line = readline("$> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			exit(1);
		}
		else
		{
			add_history(line);
			cmd = findpath(line, env);
			if (!cmd)
				continue ;
			else
				printf("%s\n", cmd);//execve
			free(line);
		}
		rl_on_new_line();
	}
	//rl_clear_history(); //not recognized
}