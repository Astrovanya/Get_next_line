/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleann <mleann@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 07:28:03 by mleann            #+#    #+#             */
/*   Updated: 2020/06/02 15:30:16 by mleann           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <sys/stat.h>

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_str;
	int				len;
	int				i;
	char			*tmp;

	if (!s1 || !s2)
		return (NULL);
	tmp = (char *)s1;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	if (!(new_str = (char *)malloc(len * sizeof(char))))
		return (NULL);
	while (*s1)
		new_str[i++] = *s1++;
	while (*s2)
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	free(tmp);
	return (new_str);
}

int					check_content(char *content, char **new_line_ptr,
									char **line)
{
	int				i;

	i = 0;
	if ((*new_line_ptr = ft_strchr(content, '\n')))
	{
		**new_line_ptr = '\0';
		if (!(*line = ft_strdup(content)))
			return (-1);
		content = ft_strcpy(content, ++(*new_line_ptr));
	}
	else
	{
		if (!(*line = ft_strdup(content)))
			return (-1);
		while (i <= BUFFER_SIZE)
			content[i++] = '\0';
	}
	return (1);
}

int					next_line(int fd, char *content, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	char			*new_line_ptr;
	int				read_bytes;

	if (BUFFER_SIZE < 1 || fd < 0 || !line || (read(fd, buf, 0) < 0) ||
		!(check_content(content, &new_line_ptr, line)))
		return (-1);
	while (!new_line_ptr && ((read_bytes = read(fd, buf, BUFFER_SIZE))))
	{
		buf[read_bytes] = '\0';
		if ((new_line_ptr = ft_strchr(buf, '\n')))
		{
			*new_line_ptr = '\0';
			ft_strcpy(content, ++new_line_ptr);
		}
		if (!(*line = ft_strjoin(*line, buf)) || read_bytes < 0)
			return (-1);
	}
	return ((ft_strlen(content) || read_bytes) ? 1 : 0);
}

static t_list		*new_list(int fd)
{
	int				i;
	t_list			*list;

	i = 0;
	if (!(list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	list->fd = fd;
	list->next = NULL;
	while (i < BUFFER_SIZE)
	{
		list->content[i] = '\0';
		i++;
	}
	return (list);
}

int					get_next_line(int fd, char **line)
{
	static t_list	*first_list;
	t_list			*iterator;
	int				flag;

	if (!first_list)
		if (!(first_list = new_list(fd)))
			return (-1);
	iterator = first_list;
	while (iterator)
	{
		if (iterator->fd == fd)
		{
			flag = next_line(fd, iterator->content, line);
			break ;
		}
		else if (iterator->next == NULL)
		{
			if (!(iterator->next = new_list(fd)))
				flag = -1;
		}
		iterator = iterator->next;
	}
	if (flag <= 0)
		ft_lstclear(&first_list);
	return (flag);
}
