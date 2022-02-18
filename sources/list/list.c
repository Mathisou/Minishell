/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:29:10 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/18 15:30:18 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_node(char  *content)
{
	t_env	*new;

	new = malloc(sizeof (t_env));
	if (!new)
		return (NULL);
	new->var = content;
	new->next = NULL;
	return (new);
}

void	add_node_back(t_env **first, char *content)
{
	t_env	*tmp;

	if (!*first)
		*first = new_node(content);
	else
	{	
		tmp = *first;
		while (tmp->next != NULL)
			tmp = (tmp)->next;
		tmp->next = new_node(content);
	}
}

int	del_list(t_env **lst)
{
	t_env	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free(*lst);
			*lst = tmp;
		}
	}
	return (0);
}

// void	del_node(t_env **envi, char *content)
// {
// 	int	check_size;

// 	check_size = ft_strlen(content);
// }