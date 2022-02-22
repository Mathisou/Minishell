/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/22 13:17:19 by maroly           ###   ########.fr       */
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

int rl3(t_global *global, char **env)
{
	int child;

	child = fork();
	if (child == 0)
	{
		if (!(tdm(global->parse->cmd)))
			if (execve(global->parse->cmd, global->parse->cmdopt, env) == -1)
				perror(global->parse->cmd);
		free(global->parse->line);
		destroy_tab(global->parse->t);
		exit(1);
	}
	else
	{
		if (tdm(global->parse->cmd))
			call_builtin(global);
		wait(NULL);
	}
	return (0);
}

int	rl2(t_global *global, char **env)
{
	add_history(global->parse->line);
	if (check_line(global->parse->line) == 1)
		ft_putstr_fd("Syntax error!\n", 2);
	else
	{
		global->parse->t = split2(global->parse->line, ' ');
		global->parse->cmd  = findpath(global->parse->t[0], global->envi); //
		check_var_and_quotes(global->parse->t, global->envi); // retire les quotes et double quotes + gere les variables denv
		global->parse->cmdopt = find_opt(global->parse->t); // a adapter
		parsing_redirection(global->parse->t, global->sfd); // > et >>
		rl3(global, env);
		free(global->parse->line);
		destroy_tab(global->parse->t);
		close(global->sfd->outfile);
		dup2(global->sfd->save_stdout, 1); // retour sur le stdout apres avoir redirige l'output avec > et >>
	}
	return (0);
}

void rl(char **env, t_global *global)
{
	struct sigaction	sa;
	t_fd sfd;
	t_parse *parse;

	parse = malloc(sizeof(t_parse));// a free
	sa.sa_handler = handler;
	global->sfd = &sfd;
	global->parse = parse;
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		parse->line = readline("$> ");
		if (!parse->line)
		{
			write(1, "exit\n", 5);
			del_list(global->envi);
			free(global->parse);
			exit(0);// free
		}
		else if (ft_strlen(parse->line) > 0)
			rl2(global,env);
		rl_on_new_line();
	}
	rl_clear_history();
}