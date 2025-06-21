/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:50:10 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/21 15:20:56 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_env_key(const char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '=' || ft_is_digits(s[0]))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!is_alnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (i != 0);
}

void	add_or_update_env(t_env **env, char *key, char *value)
{
	t_env	*cur;
	t_env	*new_node;
	t_env	*last;

	last = NULL;
	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			cur->data = NULL;
			cur->data = ft_strdup(value);
			return ;
		}
		last = cur;
		cur = cur->next;
	}
	new_node = env_new_node(ft_strdup(key), ft_strdup(value));
	if (last)
		last->next = new_node;
	else
		*env = new_node;
}

static void	print_msg_error(char *s)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	pars_export(char *s)
{
	if (s[0] == '=')
	{
		if (s[1] == ' ')
			ft_putstr_fd("minishell: export: `=': not a valid identifier\n", 2);
		else
			print_msg_error(s);
		g_exit_status = 1;
		return (-1);
	}
	return (1);
}

static int	export_helper(t_env **env, char *s)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(s, '=');
	if (equal)
	{
		key = ft_substr(s, 0, equal - s);
		value = ft_strdup(equal + 1);
	}
	else
	{
		key = s;
		value = NULL;
	}
	if (!is_valid_env_key(key))
	{
		print_msg_error(s);
		g_exit_status = 1;
		return (0);
	}
	if (value)
		add_or_update_env(env, key, value);
	return (1);
}

void	exec_export(t_env **env, t_exec **cmd)
{
	int	i;

	i = 1;
	if (!cmd || !cmd[0])
		return ;
	while ((*cmd)->args[i])
	{
		if (pars_export((*cmd)->args[i]) == -1)
			return ;
		if (!export_helper(env, (*cmd)->args[i]))
			return ;
		i++;
	}
	g_exit_status = 0;
}
