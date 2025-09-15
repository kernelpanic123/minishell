/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:55:31 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/15 15:46:54 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_env_list(t_env **env, char **envp)
{
	char **dupe;
	char *value;
	char *variable;
	int i;
	
	dupe = copy_env(envp);
	i = 0;
	while (dupe[i])
	{
		value = get_value(dupe[i]);
		variable = get_variable(dupe[i]);
		addback_env(env, variable, value);
		i++;
	}
	free(dupe);
}
void free_env_copy(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void free_list_env(t_env **list)
{
	t_env *tmp;
	t_env *clone;

	if (!list)
		return ;
	clone = *list;
	while (clone)
	{
		tmp = clone->next;
		free(clone->value);
		free(clone->variable);
		free(clone);
		clone = tmp;
	}
	*list = NULL;
}