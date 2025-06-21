/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:39:16 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 11:48:31 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*new_node(char *content)
{
	t_lst	*node;

	node = ft_malloc(sizeof(t_lst), 1);
	if (!node)
		return (NULL);
	node->content = content;
	node->type = 0;
	node->next = NULL;
	return (node);
}

void	add_back(t_lst **lst, t_lst *node)
{
	t_lst	*last;

	if (!lst || !node)
		return ;
	if (*lst)
	{
		last = last_node(*lst);
		last->next = node;
	}
	else
		*lst = node;
}

t_lst	*last_node(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_to_lst(t_lst **lst, char *content)
{
	t_lst	*node;

	node = new_node(content);
	add_back(lst, node);
}
