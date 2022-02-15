/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:21:55 by maroly            #+#    #+#             */
/*   Updated: 2021/11/21 14:09:52 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	len(int nb, int size_of_base)
{
	long int	nbr;
	int			size;

	size = 0;
	nbr = nb;
	if (nbr == -2147483648)
	{
		nbr = -nbr;
		size++;
	}
	if (nbr < 0)
	{
		nbr = -nbr;
		size++;
	}
	if (nbr < size_of_base)
		return (size);
	while (nbr >= size_of_base)
	{
		nbr = nbr / size_of_base;
		size++;
	}
	return (size);
}

static char	*dec_to_base_to(long int nb, int b_size, char *str, char *b_to)
{
	int	i;
	int	j;

	i = len(nb, b_size);
	j = i + 1;
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	while (nb >= b_size)
	{
		str[i] = b_to[nb % b_size];
		nb = nb / b_size;
		i--;
	}
	str[i] = b_to[nb % b_size];
	str[j] = '\0';
	return (str);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		intdecimal;
	int		size_to_malloc;
	int		base_to_size;
	char	*str;

	intdecimal = 0;
	base_to_size = ft_strlen(base_to);
	size_to_malloc = 0;
	if (ft_check_base(base_from) && ft_check_base(base_to))
	{
		intdecimal = ft_atoi_base(nbr, base_from);
		size_to_malloc = len(intdecimal, base_to_size) + 1;
		str = NULL;
		str = malloc(sizeof(char) * size_to_malloc);
		if (str == NULL)
			return (NULL);
		return (dec_to_base_to(intdecimal, base_to_size, str, base_to));
	}
	else
		return (NULL);
}
