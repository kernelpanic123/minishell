/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 00:57:53 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/01 16:29:52 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_char(char *input, int *i, char *result, int *j, t_expand *exp)
{
	if (input[*i] == '\'' && !exp->in_double)
	{
		exp->in_single = !exp->in_single;
		result[(*j)++] = input[(*i)++];
	}
	else if (input[*i] == '"' && !exp->in_single)
	{
		exp->in_double = !exp->in_double;
		result[(*j)++] = input[(*i)++];
	}
	else if (input[*i] == '$' && !exp->in_single && input[*i + 1])
		expand_var_in_result(input, i, result, j, exp->env, exp->exit_status);
	else
		result[(*j)++] = input[(*i)++];
}
char	*expand_variables(char *input, t_env *env, t_data *data, int exit_status)
{
	int			size;
	char		*result;
	int			i;
	int			j;
	t_expand	exp;

	size = calculate_expanded_size(input, env, data);
	result = malloc(size);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	exp.in_single = false;
	exp.in_double = false;
	exp.env = env;
	exp.exit_status = exit_status;
	while (input[i])
		process_char(input, &i, result, &j, &exp);
	result[j] = '\0';
	return (result);
}
char	*process_expansion(char *input, t_env *env, t_data *data, int exit_status)
{
	if (!input)
		return (ft_strdup(""));
	if (!env || !data)
		return (ft_strdup(input));
	return (expand_variables(input, env, data, exit_status));
}

