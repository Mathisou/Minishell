/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:30:05 by maroly            #+#    #+#             */
/*   Updated: 2021/10/19 13:30:07 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int	i;

	i = 0;
	str = ft_strlowcase(str);
	while (str[i])
	{
		if ((!((str[i - 1] >= 65 && str[i - 1] <= 90)
					|| (str[i - 1] >= 97 && str[i - 1] <= 122)
					|| (str[i - 1] >= 48 && str[i - 1] <= 57))
				&& (str[i] >= 97 && str[i] <= 122)))
			str[i] -= 32;
		i++;
	}
	return (str);
}
