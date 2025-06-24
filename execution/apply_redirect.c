/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:23:12 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/24 19:25:41 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	close(*fd);
	dup2(*fd, STDOUT_FILENO);
}

void	handle_her_doc(int *fd, char *file, t_herdoc *herdoc)
{
	int fd2;
	ssize_t count;
	
	count = 0;
	fd2 = open (file, O_WRONLY | O_CREAT | O_EXCL);
	if (fd2 < 0)
	{
		perror("");
		return ;
	}
	while (herdoc)
	{
		if (!herdoc->next)
			break;
		herdoc = herdoc->next;
	}
	while (herdoc->list)
	{
		count = write(fd2, herdoc->list->str, str_len(herdoc->list->str));
		if (count < 0)
			return ;
		herdoc->list = herdoc->list->next;
	}
	*fd = open(file, O_RDONLY);
	unlink(file);
	dup2(*fd, STDIN_FILENO);
	close(*fd);
	close(fd2);
}

int	apply_redirect(t_final_struct *tmp)
{
	int				fd;
	int				redirect;
	char			*file;
	int flag = 0;

	if (!pars_red(tmp->redirect))
		return (-1);
	while (tmp->redirect)
	{
		redirect = tmp->redirect->type;
		file = tmp->redirect->next->str;
		if (tmp->redirect->next->type == var && file[0] == '\0')
			return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), -1);
		if (redirect == op_redirect_input)
			handle_input(&fd, file);
		else if (redirect == op_redirect_output)
			handle_output(&fd, file);
		else if (redirect == op_append)
			handle_append(&fd, file);
		else if (flag == 0 && redirect == op_herdoc)
		{
			flag = 1;
			handle_her_doc(&fd, file, tmp->herdoc);
		}
		else
			return (-1);
		tmp->redirect = tmp->redirect->next->next;
	}
	return (0);
}
