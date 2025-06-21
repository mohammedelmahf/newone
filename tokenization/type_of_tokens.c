/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:50:08 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/07 10:29:58 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(t_lst *lst)
{
	if (!ft_strcmp(lst->content, "<"))
	{
		lst->type = op_redirect_input;
		return (1);
	}
	else if (!ft_strcmp(lst->content, ">"))
	{
		lst->type = op_redirect_output;
		return (1);
	}
	else if (!ft_strcmp(lst->content, "<<"))
	{
		lst->type = op_herdoc;
		return (1);
	}
	else if (!ft_strcmp(lst->content, ">>"))
	{
		lst->type = op_append;
		return (1);
	}
	return (0);
}

int	is_pipe(t_lst *lst)
{
	if (!lst)
		return (0);
	if (!ft_strcmp((lst)->content, "|"))
	{
		(lst)->type = op_pipe;
		return (1);
	}
	return (0);
}

void	tokens_type(t_lst *lst)
{
	while (lst)
	{
		while (lst && !is_operator(lst->content))
		{
			lst->type = word;
			lst = lst->next;
		}
		if (lst && is_pipe(lst))
			(lst) = (lst)->next;
		if (lst && is_redirection(lst))
			lst = lst->next;
	}
}
