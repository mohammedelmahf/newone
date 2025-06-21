/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:26:17 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 11:39:57 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == '\0')
				return ("end of file");
		}
		i++;
	}
	return (NULL);
}

t_lst	*new_node_c(t_lst *node)
{
	t_lst	*new_node;

	new_node = ft_malloc(sizeof(t_lst), 1);
	if (!new_node)
		return (NULL);
	new_node->content = node->content;
	new_node->type = node->type;
	new_node->next = NULL;
	return (new_node);
}

void	add_to_lst_c(t_lst **lst, t_lst *node)
{
	t_lst	*new_node;

	new_node = new_node_c(node);
	add_back(lst, new_node);
}

void	add_tolst(t_lst **lst, t_cmd **cmd)
{
	add_to_lst_c(&(*cmd)->redirect, *lst);
	*lst = (*lst)->next;
	add_to_lst_c(&(*cmd)->redirect, *lst);
	*lst = (*lst)->next;
}

t_cmd	*creat_cmd_struct(t_cmd **cmd, t_lst *lst)
{
	t_cmd	*head;

	*cmd = node();
	head = *cmd;
	while (lst)
	{
		while (lst && lst->type == word)
		{
			add_to_lst_c(&(*cmd)->arg, lst);
			lst = lst->next;
		}
		if (lst && lst->type != op_pipe)
			add_tolst(&lst, cmd);
		if (lst && lst->type == op_pipe)
		{
			(*cmd)->next = node();
			*cmd = (*cmd)->next;
			lst = lst->next;
		}
	}
	return (head);
}
