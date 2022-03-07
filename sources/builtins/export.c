/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:46 by maroly            #+#    #+#             */
/*   Updated: 2022/03/07 15:06:05 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_line(t_env **lst, char *to_export, t_global *global)
{
	t_env	*tmp;
	char	*str_export;
	int		i;

	tmp = *lst;
	i = -1;
	str_export = ft_strdup(to_export);
	if (!str_export)
		free_n_exit(global);
	while (str_export[++i] && str_export[i] != '=')
		;
	str_export[i] = '\0';
	while (tmp && ft_strncmp(tmp->var, str_export, i))
		tmp = tmp->next;
	free(str_export);
	free(tmp->var);
	tmp->var = ft_strdup(to_export);
	if (!tmp->var)
		free_n_exit(global);
}

static int	test(char *line, t_norm2 *nrm, t_env **lst)
{
	nrm->i = -1;
	nrm->tmp = *lst;
	nrm->str = NULL;
	while (line[++(nrm->i)] && line[nrm->i] != '=')
		if (!((line[nrm->i] >= 65 && line[nrm->i] <= 90)
				|| (line[nrm->i] >= 97 && line[nrm->i] <= 122)
				|| line[nrm->i] == 95))
			return (2);
	return (0);
}

int	check_line_to_export(char *line, t_env **lst, t_global *global)
{
	t_norm2	nrm;

	if (test(line, &nrm, lst))
		return (2);
	if (line[nrm.i])
	{
		nrm.str = ft_strdup(line);
		if (!nrm.str)
			free_n_exit(global);
		nrm.str[nrm.i] = '\0';
		while (nrm.tmp)
		{
			if (ft_strncmp(nrm.tmp->var, nrm.str, nrm.i) == 0)
			{
				free(nrm.str);
				return (1);
			}
			nrm.tmp = nrm.tmp->next;
		}
		free(nrm.str);
		return (0);
	}
	else
		return (3);
}

void	export_b(t_env **lst, char **to_export, t_global *global, int sign)
{
	int	i;
	int	rtn;

	i = 0;
	while (to_export[++i])
	{
		rtn = check_line_to_export(to_export[i], lst, global);
		if (rtn == 0)
			add_node_back(lst, to_export[i], global);
		else if (rtn == 1)
			replace_line(lst, to_export[i], global);
		else if (sign)
		{
			if (rtn == 2)
				ft_putstr_fd("Syntax error!\n", 2);
			free_in_child(global);
			exit (130);
		}
	}
	if (sign == 1)
	{
		free_in_child(global);
		exit (EXIT_SUCCESS);
	}
}
