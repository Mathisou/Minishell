/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/24 16:50:57 by maroly           ###   ########.fr       */
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

int rl3(t_global *global)
{
	int child;
	char **big;

	// int i = -1;						//print bt
	// while (global->parse->bt[++i])
	// {
	// 	int j = -1;
	// 	while(global->parse->bt[i][++j])
	// 		printf("%s ", global->parse->bt[i][j]);
	// 	printf("\n");
	// }
	child = fork();
	if (child == 0)
	{
		big = convert_env(global->envi);
		if (global->parse->cmd[0] != NULL && !(tdm(global->parse->cmd[0])))
			if (execve(global->parse->cmd[0], global->parse->cmdopt[0], big) == -1)
				perror(global->parse->cmd[0]);
		free(global->parse->line);
		destroy_tab(global->parse->t);
		del_list(global->envi);
		destroy_tab(big);
		exit(1);
	}
	else
	{
		if (global->parse->cmd[0] != NULL && tdm(global->parse->cmd[0]))
			call_builtin(global);
		wait(NULL);
	}
	return (0);
}

int	rl2(t_global *global)
{
	add_history(global->parse->line);
	if (check_line(global->parse->line) == 1)
		ft_putstr_fd("Syntax error!\n", 2);
	else
	{
		global->parse->t = split2(global->parse->line, ' ');
		check_var_and_quotes(global->parse->t, global->envi); // retire les quotes et double quotes + gere les variables denv
		pipe_split(global);
		find_cmd(global);
		global->parse->cmdopt = find_opt(global->parse->bt);
		parsing_redirection(global->parse->t, global->sfd); // to-do : < et <<
		//implementer pipex a la place de rl3
		rl3(global);
		free_end_line(global);
		close(global->sfd->outfile); //to-do: close et dup quand il faut
		dup2(global->sfd->save_stdout, 1); // retour sur le stdout apres avoir redirige l'output avec > et >>
	}
	return (0);
}

void rl(t_global *global)
{
	struct sigaction	sa;
	t_fd sfd;
	t_parse *parse;

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