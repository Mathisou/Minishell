/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/17 14:28:21 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remplace_str(char *old_str)
{
	int i;
	int j;
	char *new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(old_str) - 1));
	if (!new)
		return (NULL);
	while (old_str[++i] && old_str[i + 1])
	{
		new[j] = old_str[i];
		j++;
	}
	new[j] = '\0';
	return (new);
}

void check_var_and_quotes(char **t)
{
	int i;
	char *tmp;

	i = -1;
	while (t[++i])
	{
		if (t[i][0] == 39)
		{
			tmp = t[i];
			free(t[i]);
			t[i] = remplace_str(tmp);
		}
	}
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
			cmd = findpath(t[0], env);
			if (check_line(line) == 1)
				printf("Syntax error!\n");//
			else if (!cmd)
				printf("Command not found!\n"); //error message
			else
			{
				check_var_and_quotes(t);
				cmdopt = find_opt(t); // a adapter
				parsing_redirection(t, sfd);
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