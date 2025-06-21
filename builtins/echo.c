/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 06:40:56 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/21 15:01:01 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_with_exit_status(const char *arg)
{
	int	i = 0;
	int	in_single_quote = 0;

	while (arg[i])
	{
		if (arg[i] == '\'' )
		{
			in_single_quote = !in_single_quote;
			putchar(arg[i]);
			i++;
		}
		else if (!in_single_quote && arg[i] == '$' && arg[i + 1] == '?')
		{
			printf("%d", g_exit_status);
			i += 2;
		}
		else
		{
			putchar(arg[i]);
			i++;
		}
	}
}

void	exec_echo(t_exec **cmd)
{
	int	newline = 1;
	int	i = 1;

	if ((*cmd)->args[i] && ft_strcmp((*cmd)->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while ((*cmd)->args[i])
	{
		print_with_exit_status((*cmd)->args[i]);
		if ((*cmd)->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	g_exit_status = 0;
}