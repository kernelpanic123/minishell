/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 01:28:30 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/08 01:28:47 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path_env(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->variable, "PATH") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
