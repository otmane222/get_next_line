/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:22:36 by oaboulgh          #+#    #+#             */
/*   Updated: 2022/11/21 01:48:30 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(t_list *head)
{
	int		j;
	t_list	*last;

	j = 0;
	if (!head)
		return (1);
	last = ft_lstlast(head);
	while (last->text[j])
	{
		if (last->text[j] == '\n')
			return (0);
		j++;
	}
	return (1);
}

void	free_node(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !*lst || !del)
		return ;
	if (lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			del((*lst)->text);
			free(*lst);
			*lst = temp;
		}
	}
	*lst = NULL;
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	if (!last)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_malloc(t_list *head, char **line)
{
	int	i;
	int	j;

	i = 0;
	while (head)
	{
		j = 0;
		while (head->text[j])
		{
			if (head->text[j] == '\n')
			{
				i++;
				break ;
			}
			j++;
			i++;
		}
		head = head->next;
	}
	(*line) = malloc (i * (sizeof(char) + 1));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
