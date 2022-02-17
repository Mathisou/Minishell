/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/17 13:58:02 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_limiter(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

char	**find_opt(char **t)
{
	int i;
	int j;
	char **cmdopt;

	i = 0;
	j = -1;
	while (t[i] && check_limiter(t[i]) == 0)
		i++;
	cmdopt = malloc(sizeof(char *) * (i + 1));
	if (!cmdopt)
		return (NULL);
	while (++j < i)
		cmdopt[j] = t[j];
	cmdopt[j] = NULL;
	return (cmdopt);
}

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
	char **t;
	t_fd *sfd;
	char **cmdopt;

	env++;
	sfd = malloc(sizeof(t_fd *) * 1);
	if (!sfd)
		return ;
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
			t = ft_split(line, ' ');
			cmdopt = find_opt(t); // a adapter
			parsing_redirection(t, sfd);
			cmd = findpath(t[0], env);
			if (check_line(line) == 1)
				printf("Syntax error!\n"); //
			else if (!cmd)
				printf("Command not found!\n"); //error message
			else
			{
				int child;
				child = fork();
				if (child == 0)
					execve(cmd, cmdopt, env);
				else
					wait(NULL);
				free(line);
				free(cmd);
				destroy_tab(t);
				//close(sfd->outfile);
				dup2(sfd->save_stdout, 1);
			}
		}
		rl_on_new_line();
	}
	rl_clear_history();
}