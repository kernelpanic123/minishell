/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:29:02 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/07 15:39:48 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pwd(t_env *list)
{
	while (list != NULL)
	{
		if (ft_strcmp(list->variable, "PWD") == 0)
			printf("%s\n", list->value);
		list = list->next;
	}
}

