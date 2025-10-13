/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 02:05:49 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 18:38:25 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *list)
{
	while (list != NULL)
	{
		printf("%s=%s\n", list->variable, list->value);
		list = list->next;
	}
	return (0);
}
