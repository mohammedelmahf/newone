/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:39:42 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/31 14:42:54 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_env **env, char *oldpwd, char *pwd)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			tmp->data = oldpwd;
		if (ft_strcmp(tmp->key, "PWD") == 0)
			tmp->data = pwd;
		tmp = tmp->next;
	}
}
