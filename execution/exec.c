/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:29:06 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/24 19:35:41 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
	{
		perror("getenv");
		return (NULL);
	}
	return (path);
}

char	*file_location(char *file, char *full_path)
{
	char	*tmp_path;
	char	*token;
	int		len;
	char	*path;

	tmp_path = ft_strdup(full_path);
	if (!tmp_path)
		return (NULL);
	token = ft_strtok(tmp_path, ":");
	while (token)
	{
		len = str_len(token) + 1 + str_len(file) + 1;
		path = ft_malloc(len, 1);
		if (!path)
			return (NULL);
		ft_strncpy(path, token, str_len(token));
		path[str_len(token)] = '\0';
		ft_strcat(path, "/");
		ft_strcat(path, file);
		if (access(path, X_OK) == 0)
			return (path);
		token = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*file_path(char *file)
{
	char	*found;
	char	*path;

	if (file && (file[0] == '/' || ft_strchr(file, '/')))
	{
		if (access(file, X_OK) == 0)
			return (ft_strdup(file));
		else
			return (NULL);
	}
	path = get_path();
	if (!path)
		return (NULL);
	found = file_location(file, path);
	return (found);
}

static void	msg_error(char *arg)
{
	int	i;

	i = 0;
	ft_putstr_fd("command not found: ", 2);
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			printf("%d", g_exit_status);
			i = i + 2;
		}
		else
			printf("%c", arg[i]);
		i++;
	}
	printf("\n");
}

int exec_cmd(char **env, t_exec **cmd, t_final_struct *struc)
{
    char    *file;

    if (!cmd || !*cmd || !(*cmd)->args || !(*cmd)->args[0])
        exit(127);

    if (is_builtins((*cmd)->args[0]) != -1)
    {
        exec_builtins(&(struc->lst_env), cmd, struc);
        exit(g_exit_status);
    }

    file = file_path((*cmd)->args[0]);
    if (!file)
    {
        msg_error((*cmd)->args[0]);
        ft_malloc(0, 0);
        exit(127);
    }
    execve(file, (*cmd)->args, env);
    exit(126);
}
