/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:24:47 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/14 02:17:59 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_env_value(t_env *env, char *variable)
{
	while (env)
	{
		if (ft_strcmp(env->variable, variable) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	get_var_name_len(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	return (len);
}

void	update_quotes_state(char c, bool *single, bool *doubl)
{
	if (c == '\'' && !(*doubl))
		*single = !(*single);
	else if (c == '"' && !(*single))
		*doubl = !(*doubl);
}

int	get_normal_var_size(char *input, int *i, t_env *env)
{
	int		size;
	int		var_len;
	char	*var_name;
	char	*var_value;

	size = 0;
	var_len = get_var_name_len(input, *i);
	if (var_len > 0)
	{
		var_name = ft_substr(input, *i, var_len);
		var_value = find_env_value(env, var_name);
		if (var_value != NULL)
			size = ft_strlen(var_value);
		free(var_name);
		*i += var_len;
	}
	else
		size = 1;
	return (size);
}

int	add_var_size(char *input, int *i, t_env *env)
{
	int		size;

	size = 0;
	(*i)++;
	if (input[*i] == '?')
	{
		size = 3;
		(*i)++;
	}
	else
		size = get_normal_var_size(input, i, env);
	return (size);
}
