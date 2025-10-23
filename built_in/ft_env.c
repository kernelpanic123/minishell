/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 02:05:49 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/23 19:21:20 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_env(t_env *list, char **args)
{
	int arg_count;

	arg_count = count_args(args);
	if (arg_count > 1)
	{
		printf("env: No such file or directory\n");
		return (1);
	}
	while (list != NULL)
	{
		printf("%s=%s\n", list->variable, list->value);
		list = list->next;
	}
	return (0);
}
