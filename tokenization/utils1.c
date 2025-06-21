/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:36:07 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/02 18:17:08 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	charchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strlcpy(char *token, char *input, int len, int j)
{
	int	i;

	i = 0;
	token = ft_malloc(sizeof(char) * len + 1, 1);
	if (!token)
		return (NULL);
	while (i < len)
	{
		token[i] = input[j + i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

int	white_space(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

int	is_redirect(t_lst *lst)
{
	if (!ft_strcmp(lst->content, "<"))
		return (1);
	else if (!ft_strcmp(lst->content, ">"))
		return (1);
	else if (!ft_strcmp(lst->content, "<<"))
		return (1);
	else if (!ft_strcmp(lst->content, ">>"))
		return (1);
	return (0);
}
