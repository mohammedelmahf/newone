/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:51:47 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/21 15:17:05 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_new_node(char *key, char *data)
{
	t_env	*node;

	if (!key || !data)
		return (NULL);
	node = ft_malloc(sizeof(t_env), 1);
	if (!node)
		return (NULL);
	node->key = key;
	node->data = data;
	node->next = NULL;
	return (node);
}

char	*get_env_key(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '=' || ft_is_digits(s[0]))
	{
		ft_putstr_fd("minishell: export `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(" : not a valid identifier\n", 2);
		return (NULL);
	}
	while (s[i] && s[i] != '=')
	{
		if (!is_alnum(s[i]) && s[i] != '_')
			return (NULL);
		i++;
	}
	return (ft_substr(s, 0, i));
}

char	*get_env_data(char *s)
{
	char	*equal;

	equal = ft_strchr(s, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

char	*get_env(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (env->data);
		env = env->next;
	}
	return (NULL);
}

void	add_env_to_list(t_env **lst, char **env)
{
	t_var_env	var;
	t_env		*temp;
	t_env		*first;

	if (!env || !*env)
		return ;
	temp = NULL;
	first = NULL;
	var.i = 1;
	first = env_new_node(get_env_key(env[0]), get_env_data(env[0]));
	if (!first)
		return ;
	temp = first;
	while (env[var.i])
	{
		var.key = get_env_key(env[var.i]);
		var.data = get_env_data(env[var.i]);
		temp->next = env_new_node(var.key, var.data);
		if (!temp->next)
			return ;
		temp = temp->next;
		var.i++;
	}
	*lst = first;
}
