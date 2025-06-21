/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:44:50 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/21 15:21:02 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cd(t_env **env, t_exec **cmd)
{
	char	*new_dir;

	if (!cmd || !(*cmd) || !env || !(*env))
		return ;
	(*env)->oldpwd = getcwd(NULL, 0);
	if ((*cmd)->args[1] && (*cmd)->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	if (!(*cmd)->args[1])
		new_dir = getenv("HOME");
	else
		new_dir = (*cmd)->args[1];
	if (chdir(new_dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(new_dir, 2);
		perror(":");
		g_exit_status = 1;
		return ;
	}
	(*env)->pwd = getcwd(NULL, 0);
	update_env(env, (*env)->oldpwd, (*env)->pwd);
	g_exit_status = 0;
}
