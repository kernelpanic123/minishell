/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:29:02 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 18:36:17 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	str[10000];

	if (getcwd(str, sizeof(str)) != NULL)
	{
		printf("%s\n", str);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
