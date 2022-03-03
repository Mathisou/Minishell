/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truc_de_merde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:20:54 by maroly            #+#    #+#             */
/*   Updated: 2022/03/03 19:27:07 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tdm(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "export") == 0)
		return (1);
	return (0);
}
