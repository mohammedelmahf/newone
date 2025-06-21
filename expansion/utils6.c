/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:19:48 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 10:41:29 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s2)
		return (s1);
	new = ft_malloc(sizeof(char) * (str_len(s1) + str_len(s2) + 1), 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

char	*char_join(char *str, int count, char c)
{
	int		j;
	char	*new_str;

	j = 0;
	new_str = ft_malloc(sizeof(char) * count + 1, 1);
	if (!new_str)
		return (NULL);
	while (str && str[j])
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j] = c;
	j++;
	new_str[j] = '\0';
	return (new_str);
}

void	check_double_quote(char **str, t_env *env, t_new_exp *exp)
{
	*str = ft_strjoin(*str, expand_double_quote(exp->string->content, env));
	if (*str == NULL)
		*str = ft_strdup("");
}

void	is_var(t_new_exp *exp, t_helper_va *va, t_env *env, t_gnl **gnl)
{
	char	*tmp;

	tmp = NULL;
	tmp = get_env(exp->string->content + 1, env);
	if (!tmp)
		exp->string->content[0] = '\0';
	va->flag = split_var_arg(tmp, &va->field_str);
	if (!va->flag)
		va->str = ft_strjoin(va->str, va->field_str);
	else
		split_str(&va->str, va->field_str, gnl, exp);
	va->field_str = NULL;
}

void	split_str(char **str, char *field_str, t_gnl **gnl, t_new_exp *exp)
{
	int	i;

	i = 0;
	if (*str && field_str[i] == ' ')
	{
		add_to_gnl_lst(gnl, *str, exp->type);
		*str = NULL;
	}
	while (field_str[i])
	{
		while (field_str[i] && field_str[i] == ' ')
			i++;
		while (field_str[i] && field_str[i] != ' ')
		{
			*str = char_join(*str, str_len(*str) + 1, field_str[i]);
			i++;
		}
		if (field_str[i] == ' ')
		{
			add_to_gnl_lst(gnl, *str, exp->type);
			*str = NULL;
		}
	}
}
