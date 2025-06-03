/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:06:08 by abtouait          #+#    #+#             */
/*   Updated: 2025/05/26 14:23:32 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *input;
    (void)envp;
    (void)argv;
    (void)argc;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
        {
            exit(0);
        }
        printf("%s\n", input);
    }
}
