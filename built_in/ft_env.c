/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:46:09 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/07 15:39:35 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_env(t_env *list)
{
	while (list != NULL)
	{
		printf("%s=%s\n", list->variable, list->value);
		list = list->next;
	}
}
