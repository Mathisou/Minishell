/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_tab_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:22:10 by maroly            #+#    #+#             */
/*   Updated: 2021/10/19 13:22:17 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_sort_string_tab(char **tab)
{
	int		i;
	int		j;
	char	*swap;
	int		size;

	i = 0;
	j = i + 1;
	size = ft_count_strings(tab);
	while (i < size)
	{
		while (j < size)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				swap = tab[i];
				tab[i] = tab[j];
				tab[j] = swap;
			}
			j++;
		}
		i++;
		j = i + 1;
	}
	tab[i] = 0;
}
