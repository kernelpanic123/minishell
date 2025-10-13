/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 03:11:34 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 19:39:55 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//EN GROS pour etre valide ne start pas par un digit, no space, no "-" no "."
void	print_export(t_env *env)
{
	while (env)
	{
		printf("%s=\"%s\"\n", env->variable, env->value);
		env = env->next;
	}
}

int	is_valid_char(char c, int first)
{
	if (first)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
			return (1);
		return (0);
	}
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!is_valid_char(str[0], 1))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!is_valid_char(str[i], 0))
			return (0);
		i++;
	}
	return (1);
}

static void	process_arg(char *arg, t_env **env)
{
	char	*var;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		printf("'%s': not valid format\n", arg);
		return ;
	}
	var = get_variable(arg);
	value = get_value(arg);
	if (value)
		update_env_var(env, var, value);
	free(var);
	free(value);
}

int	ft_export(char **args, t_env **env)
{
	int	i;

	if (!args[1])
	{
		print_export(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		process_arg(args[i], env);
		i++;
	}
	return (0);
}
