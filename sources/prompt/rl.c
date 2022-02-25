/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/25 15:23:20 by maroly           ###   ########.fr       */
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

int rl3(t_global *global, int i)
{
	int child;
	char **big;

	// int k = -1;						//print bt
	// while (global->parse->bt[++k])
	// {
	// 	int j = -1;
	// 	while(global->parse->bt[k][++j])
	// 		printf("%s ", global->parse->bt[k][j]);
	// 	printf("\n");
	// }
	// printf("\n");
	child = fork();
	if (child == 0)
	{
		// int j = -1;
		// while (global->parse->cmdopt[i][++j])
		// 	printf("cmdopt : %s\n",  global->parse->cmdopt[i][j]);
		// printf("\n");
		big = convert_env(global->envi);
		free(global->parse->line);
		destroy_tab(global->parse->t);
		if (global->parse->cmd[i] != NULL && !(tdm(global->parse->cmd[i])))
			if (execve(global->parse->cmd[i], global->parse->cmdopt[i], big) == -1)
				perror(global->parse->cmd[i]);
		del_list(global->envi);
		destroy_tab(big);
		exit(1);
	}
	else
	{
		if (global->parse->cmd[i] != NULL && tdm(global->parse->cmd[i]))
			call_builtin(global, i);
		wait(NULL);
	}
	return (0);
}

int	rl2(t_global *global)
{
	//int i = -1;
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
		//while (global->parse->bt[++i])
		//{
			//parsing_redirection(global->parse->bt[i], global->sfd); // to-do : < et <<
			//rl3(global, 0); //implementer pipex a la place de rl3
			//close(global->sfd->outfile); //to-do: close et dup quand il faut
			//dup2(global->sfd->save_stdout, 1); // retour sur le stdout apres avoir redirige l'output avec > et >>
		//}
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