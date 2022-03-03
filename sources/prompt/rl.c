/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/03 19:32:15 by hkovac           ###   ########.fr       */
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
			if (!(global->parse->cmd[0] != NULL && tdm(global->parse->cmd[0])) && ft_strcmp(global->parse->cmd[0], "exit") != 0)
			{
				execute(global, 0);
				free_in_child(global);
			}
			exit(1);
		}
		else
		{
			if (ft_strcmp(global->parse->cmd[0], "exit") == 0
				&& count_triple_tab(global->parse->bt) == 1)
				exit_b(global);
			pid_add_node_back(global->pid, global->parse->child);
			wait_func(global);
		}
	}
	reset_stdin_stdout(global);
}

int	check_line_redirection(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		if ((ft_strcmp(t[i], ">") == 0 || ft_strcmp(t[i], ">>") == 0
				|| ft_strcmp(t[i], "<") == 0 || ft_strcmp(t[i], "<<") == 0
				|| ft_strcmp(t[i], "|") == 0) && t[i + 1] == NULL)
			return (1);
		else if ((ft_strcmp(t[i], ">") == 0 || ft_strcmp(t[i], ">>") == 0
				|| ft_strcmp(t[i], "<") == 0 || ft_strcmp(t[i], "<<") == 0
				|| ft_strcmp(t[i], "|") == 0) && ft_strcmp(t[i + 1], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	rl2(t_global *global)
{
	add_history(global->parse->line);
	if (check_line(global->parse->line) == 1)
		ft_putstr_fd("Syntax error!\n", 2);
	else
	{
		global->parse->t = split2(global->parse->line, ' ');
		if (check_line_redirection(global->parse->t) == 1)
		{
			destroy_tab(global->parse->t);
			ft_putstr_fd("Syntax error!\n", 2);
			return ;
		}
		check_var_and_quotes(global->parse->t, global->envi, global);
		pid_del_list(global->pid);
		pipe_split(global);
		find_cmd(global);
		global->parse->cmdopt = find_opt(global->parse->bt, global);
		if (count_triple_tab(global->parse->bt) > 1)
			pipex(global);
		else if (count_triple_tab(global->parse->bt) == 1)
			exec_one_cmd(global);
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
	*parse = (t_parse){0};
	global->sfd = &g_sfd;
	global->parse = parse;
	while (42)
	{
		init_rl(global);
		global->parse->line = readline("minishell$ ");
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
	}
}
