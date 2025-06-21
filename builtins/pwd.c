/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:36:58 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/31 14:50:57 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pwd(t_env **env)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		if ((*env)->pwd)
			printf("%s\n", (*env)->pwd);
		else
		{
			perror("pwd");
			g_exit_status = 1;
		}
	}
	else
		printf("%s\n", buffer);
	free(buffer);
	g_exit_status = 0;
}
