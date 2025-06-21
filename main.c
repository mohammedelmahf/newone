/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:04:20 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/21 15:16:31 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty__line(void)
{
	ft_malloc(0, 0);
	exit(1);
}

int	tokenize_input(char *line, t_cmd **cmd)
{
	int		status;
	t_lst	*lst;
	char	*err_msg;

	if (!line)
		empty__line();
	lst = NULL;
	err_msg = NULL;
	status = 0;
	split_input(line, &lst);
	if (lst)
	{
		tokens_type(lst);
		err_msg = pipe_line(lst, &status);
		if (err_msg)
		{
			error_msg(err_msg, status);
			status = 0;
			lst = NULL;
			return (0);
		}
		else
			*cmd = creat_cmd_struct(cmd, lst);
	}
	return (1);
}

t_final_struct	*fill_fnl(t_cmd *cmd, t_final_struct *fnl, t_env *list)
{
	t_new_exp		*exp;
	t_herdoc		*herdoc;
	int				flag;
	t_final_struct	*tmp;

	exp = NULL;
	tmp = NULL;
	flag = 0;
	herdoc = NULL;
	while (cmd)
	{
		if (flag == 1)
			herdoc = fill_herdoc(cmd->redirect, list, &herdoc);
		if (flag == 0)
		{
			herdoc = fill_herdoc(cmd->redirect, list, &herdoc);
			fnl = creat_new_exp(list, &exp, cmd, &fnl);
			tmp = fnl;
			flag = 1;
		}
		fnl->herdoc = herdoc;
		cmd = cmd->next;
		fnl = fnl->next;
	}
	return (tmp);
}

void	handle_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

int				g_exit_status;

int	main(int ac, char **av, char **env)
{
	char			*test_line;
	t_final_struct		*fnl;
	t_cmd			*cmd;
	t_env			*list;

	test_line = NULL;
	fnl = NULL;
	cmd = NULL;
	list = NULL;
	add_env_to_list(&list, env);
	(void)ac;
	(void)av;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		test_line = readline("minishell~ ");
		if(!test_line)
		{
			ft_malloc(0 , 0);
			printf("exit\n");
			exit(0);
		}
		add_history(test_line);
		if (!tokenize_input(test_line, &cmd))
			continue ;
		fnl = fill_fnl(cmd, fnl, list);
		if (fnl)
			execute(fnl, list, env);
		cmd = NULL;
		fnl = NULL;
	}
}

