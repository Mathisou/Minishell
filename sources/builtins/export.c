/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:46 by maroly            #+#    #+#             */
/*   Updated: 2022/02/28 17:48:59 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_line(t_env **lst, char *to_export)
{
	t_env	*tmp;
	char	*str_export;
	int		i;

	tmp = *lst;
	i = -1;
	str_export = ft_strdup(to_export);
	while (str_export[++i] && str_export[i] != '=')
		;
	str_export[i] = '\0';
	while (tmp && ft_strncmp(tmp->var, str_export, i))
		tmp = tmp->next;
	free(str_export);
	free(tmp->var);
	tmp->var = ft_strdup(to_export);
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

int	check_line_to_export(char *line, t_env **lst)
{
	t_norm2	nrm;

	if (test(line, &nrm, lst))
		return (2);
	if (line[nrm.i])
	{
		nrm.str = ft_strdup(line);
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
		return (2);
}

void	export(t_env **lst, char **to_export)
{
	int	i;
	int	rtn;

	i = 0;
	while (to_export[++i])
	{
		rtn = check_line_to_export(to_export[i], lst);
		if (rtn == 0)
			add_node_back(lst, to_export[i]);
		else if (rtn == 1)
			replace_line(lst, to_export[i]);
		else
			ft_putstr_fd("Syntax error!\n", 2);
	}
}
