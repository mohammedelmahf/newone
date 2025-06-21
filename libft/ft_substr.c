/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:09:34 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/20 08:20:57 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*sub;
	int		i;
	int		s_length;

	i = 0;
	if (!s)
		return (NULL);
	s_length = strlen(s);
	if (start >= s_length)
		return (ft_strdup(""));
	if (len > s_length - start)
		len = s_length - start;
	sub = ft_malloc(len + 1, 1);
	if (!sub)
		return (NULL);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
