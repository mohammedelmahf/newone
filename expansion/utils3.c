/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:18:49 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 10:41:09 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_final_struct	*fnl_node(void)
{
	t_final_struct	*new_node;

	new_node = ft_malloc(sizeof(t_final_struct), 1);
	if (!new_node)
		return (NULL);
	new_node->args = NULL;
	new_node->redirect = NULL;
	new_node->herdoc = NULL;
	new_node->lst_env = NULL;
	new_node->next = NULL;
	return (new_node);
}

int	redirect_type(char *str)
{
	if (str && !ft_strcmp(str, "<<"))
		return (2);
	if (str && !ft_strcmp(str, "<"))
		return (0);
	if (str && !ft_strcmp(str, ">>"))
		return (3);
	if (str && !ft_strcmp(str, ">"))
		return (1);
	return (-1);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	var_char(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	str_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
