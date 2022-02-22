/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:15:28 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/22 16:07:03 by hkovac           ###   ########.fr       */
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

char **convert_env(t_env **lst)
{
	t_env *tmp;
	char **big;
	int i;
	int size;

	i = 0;
	tmp = *lst;
	size = lst_size(lst);
	if (size == 0)
		return (NULL); //a securiser
	big = malloc(sizeof(*big) * (size + 1));
	if (!big)
		return (NULL); // a securiser
	while (tmp)
	{
		big[i] = ft_strdup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	big[i] = NULL;
	return (big);
}

int rl3(t_global *global)
{
	int child;
	char **big;

	child = fork();
	if (child == 0)
	{
		big = convert_env(global->envi);
		if (!(tdm(global->parse->cmd)))
			if (execve(global->parse->cmd, global->parse->cmdopt, big) == -1)
				perror(global->parse->cmd);
		free(global->parse->line);
		destroy_tab(global->parse->t);
		del_list(global->envi);
		destroy_tab(big);
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

int	rl2(t_global *global)
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
		rl3(global);
		close(global->sfd->outfile);
		dup2(global->sfd->save_stdout, 1); // retour sur le stdout apres avoir redirige l'output avec > et >>
	}
	return (0);
}

void rl(t_global *global)
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
			rl2(global);
		free(global->parse->line);
		destroy_tab(global->parse->t);
		free (global->parse->cmdopt);
		free (global->parse->cmd);
		rl_on_new_line();
	}
	rl_clear_history();
}