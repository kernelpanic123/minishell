/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 03:41:36 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/22 08:42:20 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	int	nombre;
	int	signe;
	int	i;

	i = 0;
	signe = 1;
	nombre = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		nombre = nombre * 10 + (str[i] - '0');
		i++;
	}
	return (nombre * signe);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static void	clean_exit(t_minishell *shell, int exit_code)
{
	free_list_token(&shell->list);
	free_cmd_list(shell->cmd_list);
	free_list_env(&shell->env);
	exit(exit_code);
}

int	ft_exit(t_minishell *shell, char **args)
{
	int	exit_code;
	int	arg_count;

	printf("exit\n");
	arg_count = count_args(args);
	if (arg_count == 1)
		clean_exit(shell, shell->exit_status);
	if (!is_numeric(args[1]))
	{
		printf("non numeric argument\n");
		clean_exit(shell, 2);
	}
	if (arg_count > 2)
	{
		printf("too many arguments\n");
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	clean_exit(shell, exit_code % 256);
	return (0);
}
