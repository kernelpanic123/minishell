/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:31:40 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 18:23:52 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoin_heredoc(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i++] = s2[j++];
	}
	result[i++] = '\n';
	result[i] = '\0';
	return (result);
}
