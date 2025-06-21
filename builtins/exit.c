/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:00:25 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/01 15:26:42 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numbers(char *arg)
{
    int i = 0;

    if (!arg)
        return 0;
    if (arg[i] == '+' || arg[i] == '-')
        i++;
    if (arg[i] == '\0') // only sign no digits
        return 0;
    while (arg[i])
    {
        if (!isdigit((unsigned char)arg[i]))
            return 0;
        i++;
    }
    return 1;
}

static int safe_str_to_long(const char *str, long *result)
{
    long res = 0;
    int sign = 1;
    int i = 0;

    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    if (str[i] == '\0')
        return 1;

    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 1;

        int digit = str[i] - '0';

        if (sign == 1)
        {
            if (res > (LONG_MAX - digit) / 10)
                return 1;
        }
        else
        {
            if (-res < (LONG_MIN + digit) / 10)
                return 1;
        }

        res = res * 10 + digit;
        i++;
    }
    *result = sign * res;
    return 0;
}

void exec_exit(t_final_struct *fnl, t_exec **cmd)
{
    long exit_code;

    if ((*cmd)->args[1] && (*cmd)->args[2])
    {
        printf("exit\nminishell: exit: too many arguments\n");
        g_exit_status = 1;
        return;
    }

    if ((*cmd)->args[1])
    {
        if (!is_numbers((*cmd)->args[1]))
        {
            printf("exit\nminishell: exit: %s: numeric argument required\n", (*cmd)->args[1]);
            ft_malloc(0, 0);
            exit(255);
        }

        if (safe_str_to_long((*cmd)->args[1], &exit_code) != 0)
        {
            printf("exit\nminishell: exit: %s: numeric argument required\n", (*cmd)->args[1]);
            ft_malloc(0, 0);
            exit(255);
        }
    }
    else
    {
        g_exit_status = 0;
        if (fnl && !fnl->next)
            printf("exit\n");
        ft_malloc(0, 0);
        exit(0);
    }

    g_exit_status = (unsigned char)exit_code;
    if (fnl && !fnl->next)
        printf("exit\n");
    ft_malloc(0, 0);
    exit(g_exit_status);
}
