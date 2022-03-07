/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/07 15:21:13 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	g_sfd;

void	wait_func(t_global *global)
{
	t_pid	*tmp;

	tmp = *global->pid;
	while (tmp)
	{
		waitpid(tmp->pid, &tmp->statu, 0);
		tmp = tmp->next;
	}
}

void	exec_one_cmd(t_global *global)
{
	if (parsing_redirection(global->parse->bt[0], global->sfd) == 0)
	{
		global->parse->child = fork();
		if (global->parse->child == 0)
		{
			execute(global, 0);
			free_in_child(global);
			exit(1);
		}
		else
		{
			if (global->parse->cmd[0]
				!= NULL && tdm(global->parse->cmd[0]))
				call_builtin(global, 0, 0);
			pid_add_node_back(global->pid, global->parse->child);
			wait_func(global);
		}
	}
	reset_stdin_stdout(global);
}

static void	rl3(t_global *global)
{
	check_var_and_quotes(global->parse->t, global->envi, global);
	pid_del_list(global->pid);
	pipe_split(global);
	find_cmd(global);
	global->parse->cmdopt = find_opt(global->parse->bt, global);
	if (count_triple_tab(global->parse->bt) > 1)
		pipex(global);
	else if (count_triple_tab(global->parse->bt) == 1
		&& ft_strlen(global->parse->cmdopt[0][0]) > 0
		&& is_a_directory(global->parse->cmdopt[0][0]) == 0)
		exec_one_cmd(global);
}

static void	rl2(t_global *global)
{
	add_history(global->parse->line);
	if (check_line(global->parse->line) == 1
		|| check_chev(global->parse->line) > 0)
		ft_putstr_fd("Syntax error!\n", 2);
	else
	{
		global->parse->t = split2(global->parse->line, ' ');
		if (check_line_redirection(global->parse->t) > 0)
		{
			destroy_tab(global->parse->t);
			ft_putstr_fd("Syntax error!\n", 2);
			return ;
		}
		rl3(global);
		if (access("here_doc", F_OK) == 0)
		{
			close(global->sfd->infile);
			unlink("here_doc");
		}
		free_end_line(global);
	}
}

void	rl(t_global *global)
{
	t_parse				*parse;
	t_pid				*pid;

	pid = NULL;
	global->pid = &pid;
	parse = malloc(sizeof(t_parse));
	if (!parse)
		free_n_exit(global);
	*parse = (t_parse){0};
	global->sfd = &g_sfd;
	global->parse = parse;
	while (42)
	{
		init_rl(global);
		global->sfd->after = false;
		global->parse->line = readline("minishell$ ");
		global->sfd->after = true;
		if (!global->parse->line)
			quit(global);
		else if (ft_strlen(global->parse->line) > 0)
			rl2(global);
		free(global->parse->line);
	}
}
