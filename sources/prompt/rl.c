/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/18 18:56:07 by maroly           ###   ########.fr       */
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
	char **t;
	t_fd *sfd;
	char **cmdopt;

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
		else if (ft_strlen(line) > 0)
		{
			add_history(line);
			if (check_line(line) == 1)
				ft_putstr_fd("Syntax error!\n", 2);
			else
			{
				t = split2(line, ' ');
				cmd = findpath(t[0], env); //
				if (!cmd)
					ft_putstr_fd("Command not found!\n", 2);
				else
				{
					check_var_and_quotes(t); // retire les quotes et double quotes + gere les variables denv
					cmdopt = find_opt(t); // a adapter
					parsing_redirection(t, sfd); // > et >>
					int child;
					child = fork();
					if (child == 0)
					{
						if (ft_strcmp(cmd, "/bin/pwd") != 0 && ft_strcmp(cmd, "/bin/echo") != 0) //cd pas trouvable
							execve(cmd, cmdopt, env);
						else
							call_builtin(cmd, t);
					}
					else
						wait(NULL);
					free(line);
					free(cmd);
					destroy_tab(t);
					close(sfd->outfile);
					dup2(sfd->save_stdout, 1); // retour sur le stdout apres avoir redirige l'output avec > et >>
				}
			}
		}
		rl_on_new_line();
	}
	//rl_clear_history();
}