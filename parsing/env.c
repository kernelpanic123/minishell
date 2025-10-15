/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:52:23 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/14 02:05:07 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//genere une sous-string de la variable du path
//boucle sur la string jusqu'au egal
char	*get_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	return (ft_substr(str, 0, i));
}

//idem mais avec sa valeur
char	*get_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	if (i > ft_strlen(str))
	{
		return (ft_strdup(""));
	}
	return (ft_substr(str, i + 1, ft_strlen(str)));
}

//copy l'env pour pouvoir la manipuler trkl
char	**copy_env(char **env)
{
	char	**dupe;
	int		i;

	i = 0;
	while (env[i])
		i++;
	dupe = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		dupe[i] = ft_strdup(env[i]);
		i++;
	}
	dupe[i] = NULL;
	return (dupe);
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

void	addback_env(t_env **list, char *variable, char *value)
{
	t_env	*new;
	t_env	*current;

	new = new_env_node(variable, value);
	if (!*list)
	{
		*list = new;
	}
	else
	{
		current = *list;
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