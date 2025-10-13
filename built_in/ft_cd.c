/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 02:32:20 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 18:38:47 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_var(t_env **env, char *var, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->variable, var) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	addback_env(env, ft_strdup(var), ft_strdup(value));
}

//AHAHAHAHAHHA CHDIR FAIT TOUT
int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	str[10000];

	if (getcwd(str, sizeof(str)))
		update_env_var(env, "OLDPWD", str);
	if (!args[1])
	{
		path = find_env_value(*env, "HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(str, sizeof(str)))
		update_env_var(env, "PWD", str);
	return (0);
}
