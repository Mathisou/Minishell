/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:12:49 by maroly            #+#    #+#             */
/*   Updated: 2022/02/16 14:50:07 by maroly           ###   ########.fr       */
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
			char **tab = ft_split(line, ' ');
			cmd = findpath(tab[0], env);
			//printf("%s\n", cmd);
			if (check_line(line) == 1)
				printf("Syntax error!\n"); //
			else if (!cmd)
				printf("Command not found!\n"); //error message
			else
			{
				int child;
				child = fork();
				if (child == 0)
					execve(cmd, tab, env); // check les options
				else
					wait(NULL);
				free(line);
				free(cmd);
			}
		}
		rl_on_new_line();
	}
	rl_clear_history(); //not recognized
}