/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:01:36 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/23 22:01:38 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_input(char *input, t_lst **lst)
{
	t_var	var;

	var.i = 0;
	var.y = 0;
	var.token = NULL;
	var.length = 0;
	while (1)
	{
		if (end_of_input(&var, input, lst))
			break ;
		if (token_operator(&var, input, lst))
			continue ;
		if (token_quote(&var.i, input, &var))
			continue ;
		if (token_dollar_sign(&var.i, input, &var))
			continue ;
		if (token_blank(&var, input, lst))
			continue ;
		var.i++;
		var.length++;
	}
	return (0);
}

int	token_operator(t_var *var, char *input, t_lst **lst)
{
	if (!charchr("<>|", input[var->i]))
		return (0);
	creat_token(var, input, lst);
	var->length++;
	if (valid_operator(input[var->i], input[var->i + 1]))
		var->length++;
	var->i += var->length;
	creat_token(var, input, lst);
	return (1);
}

int	end_of_input(t_var *var, char *input, t_lst **lst)
{
	if (input[var->i])
		return (0);
	if (var->length > 0)
	{
		var->token = ft_strlcpy(var->token, input, var->length, var->y);
		add_to_lst(lst, var->token);
	}
	return (1);
}

int	creat_token(t_var *var, char *input, t_lst **lst)
{
	if (var->length == 0)
		return (0);
	var->token = ft_strlcpy(var->token, input, var->length, var->y);
	add_to_lst(lst, var->token);
	var->token = NULL;
	var->length = 0;
	var->y = var->i;
	return (1);
}

int	token_blank(t_var *var, char *input, t_lst **lst)
{
	if (!white_space(input[var->i]))
		return (0);
	if (var->length > 0)
	{
		var->token = ft_strlcpy(var->token, input, var->length, var->y);
		add_to_lst(lst, var->token);
		var->token = NULL;
		var->length = 0;
	}
	while (white_space(input[var->i]))
		var->i++;
	var->y = var->i;
	return (1);
}
