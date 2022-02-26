/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/26 16:54:41 by maroly           ###   ########.fr       */
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

void	exec_one_cmd(t_global *global)
{
	char **big;

	parsing_redirection(global->parse->bt[0], global->sfd);
	global->parse->child = fork();
	if (global->parse->child == 0)
	{
		if (!(global->parse->cmd[0] != NULL && tdm(global->parse->cmd[0])))
		{
			big = convert_env(global->envi);
			execve(global->parse->cmd[0], global->parse->cmdopt[0], big);
			free(global->parse->line);
			destroy_tab(global->parse->t);
			destroy_big_tab(global->parse->bt);
			del_list(global->envi);
			destroy_tab(big);
			pid_del_list(global->pid);
		}
		exit(1);
	}
	else
	{
		if (global->parse->cmd[0] != NULL && tdm(global->parse->cmd[0]))
			call_builtin(global, 0);
		wait(NULL);
	}
	if (global->sfd->is_output_redirected == true)
	{
		close(global->sfd->outfile);
		dup2(global->sfd->save_stdout, STDOUT_FILENO);
	}
	else if (global->sfd->is_input_redirected == true)
	{
		close(global->sfd->infile);
		dup2(global->sfd->save_stdin, STDIN_FILENO);
	}
}

int	rl2(t_global *global)
{
	add_history(global->parse->line);
	if (check_line(global->parse->line) == 1) // gerer le cas ou > >> < << suivis de rien
	{
		free(global->parse->line);
		ft_putstr_fd("Syntax error!\n", 2);
	}
	else
	{
		global->parse->t = split2(global->parse->line, ' ');
		check_var_and_quotes(global->parse->t, global->envi, global);
		pid_del_list(global->pid);
		pipe_split(global);
		find_cmd(global);
		global->parse->cmdopt = find_opt(global->parse->bt);
		if (count_triple_tab(global->parse->bt) > 1)
			pipex(global);
		else
			exec_one_cmd(global);
		if (access("here_doc", F_OK) == 0)
			unlink("here_doc");
		free_end_line(global);
	}
	return (0);
}

void	find_minishell_exec(t_global *global, char *pwd)
{
	char *tmp;
	char *tmp2;
	char *tmp3;

	tmp2 = find_var(global->envi, "PWD=");
	tmp = strcats("/", tmp2);
	free(tmp2);
	if (pwd[0] == '.')
		global->parse->path_minishell = strcats(tmp, ++pwd);
	else
	{
		tmp3 = strcats("/", pwd);
		global->parse->path_minishell = strcats(tmp, tmp3);
		free(tmp3);
	}
	free(tmp);
}

void rl(t_global *global, char *pwd)
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
	find_minishell_exec(global, pwd); //marche que pour le premier appel de minishell
	//printf("%s\n", global->parse->path_minishell);
	while (1)
	{
		sigaction(SIGINT, &sa, NULL); //CTRL \ PAS GERER
		global->parse->line = readline("$> ");
		if (!global->parse->line)
		{
			write(1, "exit\n", 5);
			del_list(global->envi);
			pid_del_list(global->pid);
			free(global->parse->path_minishell);
			free(global->parse);
			exit(0);
		}
		else if (ft_strlen(global->parse->line) > 0)
			rl2(global);
		else
			free(global->parse->line);
		rl_on_new_line();
	}
	rl_clear_history();
}