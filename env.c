/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:52:23 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/14 19:32:23 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_variable(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	return (ft_substr(str, 0, i));
}

char *get_value(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	if (i > ft_strlen(str))
	{
		printf("here\n");
		return (ft_strdup(""));
	}
	return (ft_substr(str, i + 1, ft_strlen(str)));
}

t_env *copy_env(char **env)
{
	t_env *return_env;
	int i;
	char *variable;
	char *value;
	
	return_env = NULL;
	i = 0;
	while (env[i])
	{
		variable = get_variable(env[i]);
		value = get_value(env[i]);
		addback_env(&return_env, new_env_node(variable, value));
		i++;
	}
	return (return_env);
}
t_env	*new_env_node(char *variable, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->value = value;
	new->variable = variable;
	new->next = NULL;
	return (new);
}
void addback_env(t_env **list, t_env *new)
{
	t_env *current;

	current = *list;

	if (!*list)
	{
		*list = new;
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
// passe a travers toute les lignes de l'env,
	// pour chaque ligne separer le avant et le apres = dans 2 variables,
	// creer une node env qui contient la variable et la valeur,
	// ajouter la node dans return_env en utilisant un addback
	// return la liste