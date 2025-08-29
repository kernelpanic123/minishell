/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:01:42 by abtouait          #+#    #+#             */
/*   Updated: 2025/08/28 14:39:04 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>


#define WORD	1    // word
#define PIPE	2    // |
#define TRUNC	3    // >
#define INPUT	4    // <
#define APPEND	5    // >>
#define HEREDOC	6    // <<

typedef struct s_lexer
{
	char	*str;
	int				i;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_data
{
	bool simple_quotes;
	bool double_quotes;
}	t_data;

#endif