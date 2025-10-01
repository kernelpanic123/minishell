/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:27:48 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/01 16:29:52 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_struct(t_data *data)
{
	data->double_quotes = false;
	data->simple_quotes = false;
}

int	process_input(t_lexer **list, char *input, t_data *data, t_env *env, int exit_status)
{
	char	*str;
	char	*expanded;

	init_struct(data);
	str = delete_espace(input, data);
	expanded = process_expansion(str, env, data, exit_status);
	add_element(expanded, list);
	free(str);
	free(expanded);
	if (!*list)
		return (0);
	if (parse(list) == 0)
		return (0);
	return (1);
}
