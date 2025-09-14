/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:52:23 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/14 16:48:16 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy_env(char **env)
{
	int i;
	char **dupe;

	i = 0;
	while (env[i])
	{
		dupe[i] = ft_strdup(env[i]);
		i++;
	}
	return (dupe);
}