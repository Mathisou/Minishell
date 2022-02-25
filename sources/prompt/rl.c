/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/25 15:31:24 by maroly           ###   ########.fr       */
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

int	rl2(t_global *global)
{
	add_history(global->parse->line);
	if (check_line(global->parse->line) == 1)
	{
		free(global->parse->line);
		ft_putstr_fd("Syntax error!\n", 2);
	}
	else
	{
		global->parse->t = split2(global->parse->line, ' ');
		check_var_and_quotes(global->parse->t, global->envi);
		pipe_split(global);
		find_cmd(global);
		global->parse->cmdopt = find_opt(global->parse->bt);
		pipex(global);
		free_end_line(global);
	}
	return (0);
}

void rl(t_global *global)
{
	struct sigaction	sa;
	t_fd sfd;
	t_parse *parse;
	t_pid	*pid;

	pid = NULL;
	global->pid = &pid;
	parse = malloc(sizeof(t_parse));
	sa = (struct sigaction){0};
	sa.sa_handler = handler;
	global->sfd = &sfd;
	global->parse = parse;
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		global->parse->line = readline("$> ");
		if (!global->parse->line)
		{
			write(1, "exit\n", 5);
			del_list(global->envi);
			free(global->parse);
			exit(0);
		}
		else if (ft_strlen(global->parse->line) > 0)
			rl2(global);
		rl_on_new_line();
	}
	rl_clear_history();
}