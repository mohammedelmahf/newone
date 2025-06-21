/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:22:47 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 10:41:36 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_string(char *str, t_new_exp **exp)
{
	t_va	va;

	va.i = 0;
	va.len = 0;
	va.start = 0;
	while (str[va.i])
	{
		if (str[va.i] == '"' || str[va.i] == '\'' || str[va.i] == '$')
		{
			if (va.len > 0)
				del_last_str(str, &va, exp);
			if (quote_string(str, &va, exp))
				continue ;
			else if (dollar_sign_string(str, &va, exp))
				continue ;
		}
		va.i++;
		va.len++;
	}
	if (va.len > 0)
		del_last_str(str, &va, exp);
}

int	split_var_arg(char *str, char **field_str)
{
	int	i;
	int	count;
	int	remainder;
	int	check;

	i = 0;
	check = 0;
	remainder = 0;
	count = 0;
	while (str && str[i])
	{
		if (skip_split_char(str, &i, &remainder, &check))
			continue ;
		count++;
		if (remainder == 1)
			add_space(field_str, &remainder, &count);
		*field_str = char_join(*field_str, count, str[i]);
		i++;
	}
	if (remainder == 1)
		*field_str = char_join(*field_str, count + 1, ' ');
	return (check + remainder);
}
