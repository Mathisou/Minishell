/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:09:38 by maroly            #+#    #+#             */
/*   Updated: 2021/10/31 23:27:32 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	find_index(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int	result;
	int	count;
	int	i;

	i = 0;
	result = 0;
	count = 1;
	if (ft_check_base(base) == 1)
	{
		while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		while (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				count *= -1;
			i++;
		}
		while (is_in_base(str[i], base) && str[i])
		{
			result = result * ft_strlen(base) + find_index(str[i], base);
			i++;
		}
		return (result * count);
	}
	return (0);
}
