/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:14:34 by maroly            #+#    #+#             */
/*   Updated: 2021/11/24 16:57:31 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	count_divide(long nb)
{
	int	size;

	size = 0;
	while (nb >= 10 || nb <= -10)
	{
		nb = nb / 10;
		size++;
	}
	if (nb < 0)
		size++;
	return (size + 1);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;
	long	nb;

	str = NULL;
	nb = n;
	size = count_divide(nb);
	str = (char *) malloc(sizeof(*str) * (size + 1));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb >= 10)
	{
		str[size - 1] = nb % 10 + 48;
		size--;
		nb = nb / 10;
	}
	str[size - 1] = nb + 48;
	return (str);
}
