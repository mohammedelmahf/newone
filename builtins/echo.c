/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:03:01 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/23 22:03:02 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_with_exit_status(const char *arg)
{
	int	i;
	int	in_single_quote;

	i = 0;
	in_single_quote = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
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
	int	newline;
	int	i;

	newline = 1;
	i = 1;
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
