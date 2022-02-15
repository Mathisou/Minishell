/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:48:20 by maroly            #+#    #+#             */
/*   Updated: 2021/10/31 23:03:49 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	convert(long nbr, int size_of_base, char *base)
{
	long	quotient;
	long	rest;

	quotient = nbr / size_of_base;
	rest = nbr % size_of_base;
	if (quotient)
		convert(quotient, size_of_base, base);
	write(1, &base[rest], 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		size_of_base;
	long	nbr2;

	nbr2 = nbr;
	size_of_base = ft_strlen(base);
	if (ft_check_base(base) == 1)
	{
		if (nbr2 < 0)
		{
			nbr2 *= -1;
			write(1, "-", 1);
		}
		convert(nbr2, size_of_base, base);
	}
	else
		return ;
}
