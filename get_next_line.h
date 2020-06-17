/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleann <mleann@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 20:25:10 by mleann            #+#    #+#             */
/*   Updated: 2020/05/29 15:14:27 by mleann           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	char			content[BUFFER_SIZE + 1];
	int				fd;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strdup(char const *s);
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);
void				ft_lstclear(t_list **lst);
#endif
