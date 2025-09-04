/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:40:08 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/04 20:40:09 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "minishell.h"

// Peek Token
int		peek_tokens(char *str, char *tokens);
void	advance_string(char *str, char c, int *i);

// Readline
int		ft_getline(void);
int		check_quotes(char *str);
int		check_invalid_tokens(char *str);

#endif