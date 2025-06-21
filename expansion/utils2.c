/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:18:08 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 10:42:21 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_last_str(char *str, t_va *va, t_new_exp **exp)
{
	char	*new_str;
	int		flag;

	new_str = NULL;
	new_str = ft_strlcpy(new_str, str, va->len, va->start);
	flag = 0;
	if (str[va->start] == '$' && check_char(str[va->start + 1]))
		flag = 6;
	else
		flag = 7;
	add_to_string_lst(&(*exp)->string, new_str, flag);
	new_str = NULL;
	va->start = va->i;
	va->len = 0;
}

int	get_flag_q(char quote)
{
	if (quote == '"')
		return (9);
	return (8);
}

int	get_flag_v(char c)
{
	if (check_char(c))
		return (6);
	return (7);
}

int	quote_string(char *str, t_va *va, t_new_exp **exp)
{
	char	quote;
	char	*new_str;

	new_str = NULL;
	if (!is_quote(str[va->i]))
		return (0);
	quote = str[va->i];
	va->i++;
	while (str[va->i] && str[va->i] != quote)
	{
		va->i++;
		va->len++;
	}
	va->i++;
	new_str = ft_strlcpy(new_str, str, va->len, va->start + 1);
	add_to_string_lst(&(*exp)->string, new_str, get_flag_q(quote));
	new_str = NULL;
	va->start = va->i;
	va->len = 0;
	return (1);
}

int	dollar_sign_string(char *str, t_va *va, t_new_exp **exp)
{
	int		flag;
	char	*new_str;

	new_str = NULL;
	flag = 0;
	if (str[va->i] != '$')
		return (0);
	va->i++;
	va->len++;
	flag = get_flag_v(str[va->i]);
	while (str[va->i] && var_char(str[va->i]))
	{
		va->i++;
		va->len++;
	}
	new_str = ft_strlcpy(new_str, str, va->len, va->start);
	add_to_string_lst(&(*exp)->string, new_str, flag);
	new_str = NULL;
	va->start = va->i;
	va->len = 0;
	return (1);
}
