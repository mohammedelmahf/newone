/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:19:37 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 10:35:17 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gnl	*last_node_gnl(t_gnl *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_gnl_back(t_gnl **lst, t_gnl *node)
{
	t_gnl	*last;

	if (!lst || !node)
		return ;
	if (*lst)
	{
		last = last_node_gnl(*lst);
		last->next = node;
	}
	else
		*lst = node;
}

void	add_to_gnl_lst(t_gnl **lst, char *content, int type)
{
	t_gnl	*node;

	node = final_node(content, type);
	add_gnl_back(lst, node);
}

int	skip_split_char(char *str, int *i, int *remainder, int *check)
{
	if (!split_char(str[*i]))
		return (0);
	(*i)++;
	*remainder = 1;
	*check = 1;
	return (1);
}

void	add_space(char **field_str, int *remainder, int *count)
{
	*field_str = char_join(*field_str, *count, ' ');
	(*count)++;
	*remainder = 0;
}
