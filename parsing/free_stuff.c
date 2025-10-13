/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:50:34 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 18:09:55 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list_token(t_lexer **list)
{
	t_lexer	*tmp;
	t_lexer	*clone;

	if (!list)
		return ;
	clone = *list;
	while (clone)
	{
		tmp = clone->next;
		free(clone->str);
		free(clone);
		clone = tmp;
	}
	*list = NULL;
}
