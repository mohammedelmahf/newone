/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:59:11 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/21 09:44:54 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_inside_quote(char *str, char **new_str, int *i)
{
	char	quote;

	if (!is_quote(str[*i]))
		return (0);
	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		*new_str = char_join(*new_str, str_len(*new_str) + 1, str[*i]);
		(*i)++;
	}
	(*i)++;
	return (1);
}

int	expand_in_herdoc(t_va *va, char *str, char **new_str, t_env *env)
{
	char	*tmp;
	char	*var_str;

	tmp = NULL;
	var_str = NULL;
	if (str[va->i] == '$' && check_char(str[va->i + 1]))
	{
		va->start = va->i;
		va->i++;
		va->len++;
		while (str[va->i] && var_char(str[va->i]))
		{
			va->i++;
			va->len++;
		}
		var_str = ft_strlcpy(var_str, str, va->len, va->start);
		tmp = get_env(var_str + 1, env);
		if (tmp)
			*new_str = ft_strjoin(*new_str, tmp);
		tmp = NULL;
		var_str = NULL;
		return (1);
	}
	return (0);
}

char	*expand_herdoc(char *str, t_env *env)
{
	char	*new_str;
	t_va	va;

	new_str = NULL;
	va.i = 0;
	va.start = 0;
	va.len = 0;
	while (str && str[va.i])
	{
		if (expand_in_herdoc(&va, str, &new_str, env))
			continue ;
		new_str = char_join(new_str, str_len(new_str) + 1, str[va.i]);
		va.i++;
	}
	return (new_str);
}

void	put_error_msg(char *str)
{
	printf("minishell: warning: ");
	printf("here-document delimited by end-of-file (wanted `%s')\n", str);
}

t_herdoc	*new_herdoc(void)
{
	t_herdoc	*node;

	node = ft_malloc(sizeof(t_herdoc), 1);
	if (!node)
		return (NULL);
	node->list = NULL;
	node->next = NULL;
	return (node);
}
