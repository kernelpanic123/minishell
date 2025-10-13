/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 02:45:06 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 18:36:29 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//si on doit supp le premier element juste deplacer la tete de lecture
void	remove_env_var(t_env **env, char *del_var)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->variable, del_var) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->variable);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(char **args, t_env **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(env, args[i]);
		i++;
	}
	return (0);
}
