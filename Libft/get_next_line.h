/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:59:48 by maroly            #+#    #+#             */
/*   Updated: 2022/02/03 23:04:31 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define BUFFER_SIZE 2048

char	*split(char *str, char *new);
size_t	ft_strlen(const char *s);
char	*value_to_return(char *new_line, char *buffer, int check);
char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
