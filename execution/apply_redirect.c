/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:23:12 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/21 15:19:30 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	type_of_redirect(char *redirect)
{
	if (!redirect)
		return (-1);
	if (ft_strcmp(redirect, "<") == 0)
		return (op_redirect_input);
	else if (ft_strcmp(redirect, ">") == 0)
		return (op_redirect_output);
	else if (ft_strcmp(redirect, ">>") == 0)
		return (op_append);
	return (-1);
}

int	append_(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open for append");
		return (-1);
	}
	return (fd);
}

void	handle_input(int *fd, char *file)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		perror("minishell");
		exit(1);
	}
	dup2(*fd, STDIN_FILENO);
	close(*fd);
}

void	handle_output(int *fd, char *file)
{
	*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
	{
		perror("");
		return ;
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

void	handle_append(int *fd, char *file)
{
	*fd = append_(file);
	if (*fd < 0)
	{
		perror("");
		return ;
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

int pars_red(t_gnl *red)
{
	int count;

	count  = 0;
	while (red)
	{
		red = red->next;
		while (red && (red->type == -1 || red->type == var))
		{
			count++;
			if (count > 1)
			{
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				return (0);
			}
			red = red->next;
		}
		count = 0;
	}
	return (1);
}

int	apply_redirect(t_final_struct *struc)
{
	int				fd;
	int				redirect;
	char			*file;
	t_final_struct	*tmp;

	tmp = struc;
	if (!pars_red(tmp->redirect))
		return (-1);
	while (tmp->redirect)
	{
		redirect = tmp->redirect->type;
		file = tmp->redirect->next->str;
		if (tmp->redirect->next->type == var && file[0] == '\0')
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			return (-1);
		}
		if (redirect == op_redirect_input && tmp->redirect->type != -1)
			handle_input(&fd, file);
		else if (redirect == op_redirect_output && tmp->redirect->type != -1)
			handle_output(&fd, file);
		else if (redirect == op_append && tmp->redirect->type != -1)
			handle_append(&fd, file);
		else
			return (-1);
		tmp->redirect = tmp->redirect->next->next;
	}
	return (0);
}
