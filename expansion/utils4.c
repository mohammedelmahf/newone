/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:19:26 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/21 14:23:45 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_var_char(char *str, int *i, int *len)
{
	while (str[*i] && var_char(str[*i]))
	{
		(*i)++;
		(*len)++;
	}
}

int	dollar_sign_in_quote(char *str, t_va *va, t_new_exp **exp)
{
	int		flag;
	char	*new_str;

	new_str = NULL;
	flag = 0;
	if (str[va->i] != '$')
		return (0);
	if (va->len > 0)
		del_last_str(str, va, exp);
	va->i++;
	va->len++;
	if (check_char(str[va->i]))
		flag = 6;
	else
		flag = 7;
	if (str[va->i] && var_char(str[va->i]))
		skip_var_char(str, &va->i, &va->len);
	new_str = ft_strlcpy(new_str, str, va->len, va->start);
	add_to_string_lst(&(*exp)->string, new_str, flag);
	new_str = NULL;
	va->start = va->i;
	va->len = 0;
	return (1);
}

char	*fnl_str(t_env *env, t_new_exp *exp)
{
	char	*new_str;
	char	*tmp;

	tmp = NULL;
	new_str = NULL;
	while (exp && exp->string)
	{
		if (exp->string->type == var)
		{
			tmp = get_env(exp->string->content + 1, env);
			if (!tmp)
				exp->string->content[0] = '\0';
			new_str = ft_strjoin(new_str, tmp);
		}
		else
			new_str = ft_strjoin(new_str, exp->string->content);
		exp->string = exp->string->next;
	}
	return (new_str);
}

char	*expand_double_quote(char *str, t_env *env)
{
	t_va		va;
	t_new_exp	*exp;

	va.len = 0;
	va.i = 0;
	va.start = 0;
	exp = NULL;
	exp = new_lst_node(-1);
	while (str[va.i])
	{
		if (dollar_sign_in_quote(str, &va, &exp))
			continue ;
		va.i++;
		va.len++;
	}
	if (va.len > 0)
		del_last_str(str, &va, &exp);
	return (fnl_str(env, exp));
}

t_gnl	*final_node(char *content, int type)
{
	t_gnl	*new_node;

	new_node = ft_malloc(sizeof(t_gnl), 1);
	if (!new_node)
		return (NULL);
	new_node->str = content;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}
