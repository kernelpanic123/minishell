/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:27:48 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 16:57:08 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_struct(t_data *data)
{
	data->double_quotes = false;
	data->simple_quotes = false;
}

int	process_input(t_lexer **list, char *input, t_data *data, t_minishell *shell)
{
	char	*str;
	char	*expanded;

	init_struct(data);
	str = delete_espace(input, data);
	expanded = process_expansion(str, shell->env, data, shell->exit_status);
	add_element(expanded, list);
	free(str);
	free(expanded);
	if (!*list)
		return (0);
	if (parse(list) == 0)
		return (0);
	return (1);
}