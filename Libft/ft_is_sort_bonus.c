/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:51:33 by maroly            #+#    #+#             */
/*   Updated: 2021/10/19 13:31:11 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_is_sort(int *tab, int length, int (*f)(int, int))
{
	int	i;
	int	j;
	int	sens;

	i = 0;
	j = 0;
	sens = 0;
	while (i < length - 1)
	{
		sens = f(tab[i], tab[i + 1]);
		if (sens > 0 && j == 0)
			j = 1;
		else if (sens < 0 && j == 0)
			j = -1;
		if (j == 1 && sens < 0)
			return (0);
		else if (j == -1 && sens > 0)
			return (0);
		i++;
	}
	return (1);
}
