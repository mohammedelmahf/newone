/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:16:28 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 10:42:14 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_new_exp	*new_lst_node(int type)
{
	t_new_exp	*new_node;

	new_node = ft_malloc(sizeof(t_new_exp), 1);
	if (!new_node)
		return (NULL);
	new_node->string = NULL;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	*new_node_(char *content, int flag)
{
	t_lst	*node;

	node = ft_malloc(sizeof(t_lst), 1);
	if (!node)
		return (NULL);
	node->content = content;
	node->type = flag;
	node->next = NULL;
	return (node);
}

void	add_to_string_lst(t_lst **lst, char *content, int flag)
{
	t_lst	*node;

	node = new_node_(content, flag);
	add_back(lst, node);
}

int	check_char(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	split_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
