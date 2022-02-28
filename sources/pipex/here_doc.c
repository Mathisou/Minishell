/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:38:27 by maroly            #+#    #+#             */
/*   Updated: 2022/02/28 16:41:51 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_check_line(char *line, char *limiter)
{
	int	j;
	int	size;

	if (!line)
		return (0);
	j = 0;
	size = ft_strlen(line) - 1;
	while (size > 0 && line[size - 1] != '\n')
		size--;
	while (limiter[j] && line[size + j] == limiter[j])
	{
		j++;
		if (limiter[j] == '\0' && line[size + j] == '\n')
			return (j);
	}
	return (0);
}

char	*ft_strcat2(char *dest, const char *src)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(dest);
	while (src[i])
	{
		dest[size + i] = (char)src[i];
		i++;
	}
	dest[size + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *)s2));
	else
	{
		new = malloc(sizeof(*new) * (ft_strlen(s2) + ft_strlen(s1) + 1));
		if (!new)
			return (NULL);
		new[0] = '\0';
		new = ft_strcat2(new, (char *)s1);
		free((char *)s1);
		return (ft_strcat2(new, (char *)s2));
	}
}

int	here_doc(t_fd *sfd, char *limiter)
{
	char	buffer[2];
	char	*line;

	line = NULL;
	sfd->is_here_doc = true;
	while (read(0, buffer, 1) != 0)
	{
		buffer[1] = '\0';
		line = ft_strjoin(line, buffer);
		if (here_doc_check_line(line, limiter) > 0 || sfd->is_sig == true)
		{
			line[ft_strlen(line) - here_doc_check_line(line, limiter) - 1] = '\0';
			break ;
		}
	}
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	sfd->here_doc_fd = open("here_doc", O_RDWR | O_APPEND | O_CREAT, 0644);
	if (sfd->here_doc_fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		close(sfd->here_doc_fd);
		return (1); //
	}
	if (sfd->is_sig == false)
		ft_putstr_fd(line, sfd->here_doc_fd);
	close(sfd->here_doc_fd);
	free(line);
	return (1);
}
