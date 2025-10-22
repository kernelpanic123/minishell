/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 03:41:36 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/22 08:22:45 by abtouait         ###   ########.fr       */
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

int	ft_exit(t_minishell *shell, char **args)
{
	int	exit_code;
	int	arg_nbr;

	printf("exit\n");
	arg_nbr = count_args(args);
	if (arg_nbr == 1)
	{
		free_list_env(&shell->env);
		exit(shell->exit_status);
	}
	if (!is_numeric(args[1]))
	{
		printf("error non numeric argument\n");
		free_list_env(&shell->env);
		exit(2);
	}
	if (arg_nbr > 2)
	{
		printf("too many arguments\n");
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	free_list_env(&shell->env);
	exit(exit_code % 256);
}
