/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 04:43:48 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/21 15:24:33 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_final_struct *fnl, int in_fd, int out_fd,
		t_env *lst_env, char **env, t_exec **exec)
{
	if (!fnl || !lst_env || !exec)
		exit(EXIT_FAILURE);
	if (apply_redirect(fnl) == -1)
		return ;
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	exec_cmd(env, exec, fnl);
	exit(EXIT_FAILURE);
}

void	execute(t_final_struct *list, t_env *lst_env, char **env)
{
	int		fd[2];
	int		in_fd;
	int		status;
	int		pid;
	t_exec	*exec;

	in_fd = STDIN_FILENO;
	if (list && !list->next && list->args && is_builtins(list->args->str) != -1
		&& !list->redirect)
	{
		exec = gnl_to_array(list->args);
		exec_builtins(&lst_env, &exec, list);
		return ;
	}
	while (list)
	{
		exec = gnl_to_array(list->args);
		if (list->next)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			fd[0] = STDIN_FILENO;
			fd[1] = STDOUT_FILENO;
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (list->next)
				close(fd[0]);
			child_process(list, in_fd, fd[1], lst_env, env, &exec);
		}
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (list->next)
			close(fd[1]);
		in_fd = fd[0];
		list = list->next;
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 1;
}
