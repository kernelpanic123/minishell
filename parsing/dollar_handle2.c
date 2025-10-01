/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 00:44:29 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/01 16:29:52 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calculate_expanded_size(char *input, t_env *env, t_data *data)
{
	int		i;
	int		size;
	bool	in_single;
	bool	in_double;

	i = 0;
	size = 0;
	in_single = false;
	in_double = false;
	while (input[i])
	{
		update_quotes_state(input[i], &in_single, &in_double);
		if (input[i] == '$' && !in_single && input[i + 1])
			size += add_var_size(input, &i, env);
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
}

void	copy_exit_status(char *result, int *j, int exit_status)
{
	char	*exit_str;
	int		k;

	exit_str = ft_itoa(exit_status);
	k = 0;
	while (exit_str[k])
	{
		result[*j] = exit_str[k];
		(*j)++;
		k++;
	}
	free(exit_str);
}

void	copy_var_value(char *result, int *j, char *var_value)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		result[*j] = var_value[k];
		(*j)++;
		k++;
	}
}

void	expand_normal_var(char *input, int *i, char *result, int *j, t_env *env)
{
	int		var_len;
	char	*var_name;
	char	*var_value;

	var_len = get_var_name_len(input, *i);
	if (var_len > 0)
	{
		var_name = ft_substr(input, *i, var_len);
		var_value = find_env_value(env, var_name);
		if (var_value)
			copy_var_value(result, j, var_value);
		free(var_name);
		*i += var_len;
	}
	else
		result[(*j)++] = '$';
}

void	expand_var_in_result(char *input, int *i, char *result, int *j, t_env *env, int exit_status)
{
	(*i)++;
	if (input[*i] == '?')
	{
		copy_exit_status(result, j, exit_status);
		(*i)++;
	}
	else
		expand_normal_var(input, i, result, j, env);
}
