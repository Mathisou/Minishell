/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_file_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:29:54 by maroly            #+#    #+#             */
/*   Updated: 2021/10/19 13:29:57 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_stock_file(char *file_name)
{
	int		i;
	int		dict;
	char	currchar;
	char	*str;

	i = 0;
	dict = open(file_name, O_RDONLY);
	if (dict == -1)
		return (0);
	while (read(dict, &currchar, 1))
		i++;
	str = (char *) malloc(sizeof(*str) * (i + 1));
	if (str == NULL)
		return (NULL);
	close(dict);
	i = 0;
	dict = open(file_name, O_RDONLY);
	while (read(dict, &str[i], 1))
		i++;
	close(dict);
	return (str);
}
