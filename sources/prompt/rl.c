/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/01 14:15:25 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	sfd;

void handler(int signum)
{
	if (signum == SIGINT)
	{
		sfd.is_sig = true;
		write(1, "\n", 1);
		if (sfd.is_here_doc == false)
			rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		//rl_on_new_line();
		//rl_replace_line("", 4098);
		//rl_replace_line("", 2);
		rl_redisplay();
	}
}

void	exec_one_cmd(t_global *global)
{
	if (parsing_redirection(global->parse->bt[0], global->sfd) == 0)
	{
		global->parse->child = fork();
		if (global->parse->child == 0)
		{
			if (!(global->parse->cmd[0] != NULL && tdm(global->parse->cmd[0])))
			{
				execute(global, 0, 0);
				free_in_child(global);
			}
			exit(1);
		}
		else
		{
			if (global->parse->cmd[0] != NULL && tdm(global->parse->cmd[0]))
				call_builtin(global, 0);
			wait(NULL);
		}
	}
	reset_stdin_stdout(global);
}

int	check_line_redirection(char **t)
{
	int i;

	i = 0;
	while (t[i])
	{
		if ((ft_strcmp(t[i], ">") == 0 || ft_strcmp(t[i], ">>") == 0 || ft_strcmp(t[i], "<") == 0 || ft_strcmp(t[i], "<<") == 0 || ft_strcmp(t[i], "|") == 0) && t[i + 1] == NULL)
			return (1);
		else if ((ft_strcmp(t[i], ">") == 0 || ft_strcmp(t[i], ">>") == 0 || ft_strcmp(t[i], "<") == 0 || ft_strcmp(t[i], "<<") == 0 || ft_strcmp(t[i], "|") == 0) && ft_strcmp(t[i + 1], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	rl2(t_global *global)
{
	add_history(global->parse->line);
	if (check_line(global->parse->line) == 1) // quotes
		ft_putstr_fd("Syntax error!\n", 2);
	else
	{
		global->parse->t = split2(global->parse->line, ' ');
		if (check_line_redirection(global->parse->t) == 1) // redirection / pipe
		{
			destroy_tab(global->parse->t);
			ft_putstr_fd("Syntax error!\n", 2);
			return (0); //
		}
		check_var_and_quotes(global->parse->t, global->envi, global);
		pid_del_list(global->pid);
		pipe_split(global);
		find_cmd(global);
		global->parse->cmdopt = find_opt(global->parse->bt);
		if (count_triple_tab(global->parse->bt) > 1)
			pipex(global);
		else if (count_triple_tab(global->parse->bt) == 1)
			exec_one_cmd(global);
		if (access("here_doc", F_OK) == 0)
			unlink("here_doc");
		free_end_line(global);
	}
	return (0);
}

void rl(t_global *global, char *pwd)
{
	struct sigaction	sa;
	t_parse *parse;
	t_pid	*pid;
	int i;
	(void)pwd;

	pid = NULL;
	global->pid = &pid;
	parse = malloc(sizeof(t_parse));
	sa = (struct sigaction){0};
	sa.sa_handler = handler;
	global->sfd = &sfd;
	global->parse = parse;
	i = 0;
	while (++i)
	{
		sigaction(SIGINT, &sa, NULL); //CTRL \ PAS GERER
		sigaction(SIGQUIT, &sa, NULL);
		global->sfd->is_sig = false;
		global->sfd->is_here_doc = false;
		global->sfd->is_input_redirected = false;
		global->sfd->is_output_redirected = false;
		global->sfd->is_stdout = false;
		global->parse->line = readline("$> ");
		if (!global->parse->line)
		{
			write(1, "exit\n", 5);
			del_list(global->envi);
			pid_del_list(global->pid);
			free(global->parse);
			rl_clear_history();
			exit(0);
		}
		else if (ft_strlen(global->parse->line) > 0)
			rl2(global);
		free(global->parse->line);
		if (i > 1)
			close(global->sfd->save_stdout);
	}
}