/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:02:35 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/23 22:02:36 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (e_echo);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (e_cd);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (e_pwd);
	else if (ft_strcmp(cmd, "export") == 0)
		return (e_export);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (e_unset);
	else if (ft_strcmp(cmd, "env") == 0)
		return (e_env);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (e_exit);
	return (-1);
}

int	exec_builtins(t_env **lst_env, t_exec **cmd, t_final_struct *struc)
{
	int	builtin_type;

	builtin_type = is_builtins((*cmd)->args[0]);
	if (builtin_type == -1)
		return (-1);
	if (builtin_type == e_echo)
		exec_echo(cmd);
	else if (builtin_type == e_pwd)
		exec_pwd(lst_env);
	else if (builtin_type == e_export)
		exec_export(lst_env, cmd);
	else if (builtin_type == e_env)
		exec_env(lst_env);
	else if (builtin_type == e_cd)
		exec_cd(lst_env, cmd);
	else if (builtin_type == e_unset)
		exec_unset(lst_env, cmd);
	else if (builtin_type == e_exit)
		exec_exit(struc, cmd);
	return (0);
}
