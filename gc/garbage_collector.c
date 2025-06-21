/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:12:31 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 10:56:39 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

t_list	**get_list(void)
{
	static t_list	*list;

	return (&list);
}

void	*ft_malloc(size_t size, int flag)
{
	t_list	*node;
	void	*ptr;

	node = NULL;
	ptr = NULL;
	if (flag == 0)
	{
		ft_lstclear(get_list(), free);
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = ft_lstnew(ptr);
	if (!node)
		return (NULL);
	ft_lstadd_front(get_list(), node);
	return (ptr);
}
