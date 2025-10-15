/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:29:02 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/14 02:24:31 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//getcwd fait un appel sys direct au kernel pour l'info
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
