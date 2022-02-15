/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:19:40 by maroly            #+#    #+#             */
/*   Updated: 2021/10/19 12:19:42 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_power(int nb, int power)
{
	if (power == 0)
		return (1);
	while (power > 0)
		return (nb * ft_power(nb, power - 1));
	return (0);
}
