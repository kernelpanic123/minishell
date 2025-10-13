/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 00:57:53 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 18:10:57 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_char(t_expand_utils *utils, t_expand *exp)
{
	if (utils->input[*utils->i] == '\'' && !exp->in_double)
	{
		exp->in_single = !exp->in_single;
		utils->result[(*utils->j)++] = utils->input[(*utils->i)++];
	}
	else if (utils->input[*utils->i] == '"' && !exp->in_single)
	{
		exp->in_double = !exp->in_double;
		utils->result[(*utils->j)++] = utils->input[(*utils->i)++];
	}
	else if (utils->input[*utils->i] == '$' && !exp->in_single
		&& utils->input[*utils->i + 1])
		expand_var_in_result(utils, exp);
	else
		utils->result[(*utils->j)++] = utils->input[(*utils->i)++];
}

static t_expand_utils	init_utils(char *input, char *result)
{
	static int		i;
	static int		j;
	t_expand_utils	utils;

	i = 0;
	j = 0;
	utils.input = input;
	utils.result = result;
	utils.i = &i;
	utils.j = &j;
	return (utils);
}

char	*expand_variables(char *input, t_env *env, int exit_status)
{
	char			*result;
	t_expand		exp;
	t_expand_utils	utils;

	result = malloc(calculate_expanded_size(input, env));
	if (!result)
		return (NULL);
	exp.in_single = false;
	exp.in_double = false;
	exp.env = env;
	exp.exit_status = exit_status;
	utils = init_utils(input, result);
	while (input[*utils.i])
		process_char(&utils, &exp);
	result[*utils.j] = '\0';
	return (result);
}

char	*process_expansion(char *input, t_env *env
		t_data *data, int exit_status)
{
	(void)data;
	if (!input)
		return (ft_strdup(""));
	if (!env)
		return (ft_strdup(input));
	return (expand_variables(input, env, exit_status));
}
