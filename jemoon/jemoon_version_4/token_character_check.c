/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_character_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:40:39 by jahong            #+#    #+#             */
/*   Updated: 2025/01/31 10:23:52 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_valid_back(char *str, int idx)
{
	if (idx > 0)
	{
		if (str[idx - 1] == '$' && ft_isdigit(str[idx]) != 0)
			return (1);
	}
	if (str[idx] == '?')
		return (1);
	if (str[idx] == '*')
		return (1);
	return (0);
}
int	check_quote_pair(char c, int quote)
{
	if (c == '\'' && quote == 0)
		quote = 1;
	else if (c == '"' && quote == 0)
		quote = 2;
	else if (c == '\'' && quote == 1) 
		quote = 0;
	else if (c == '"' && quote == 2)
		quote = 0;
	return (quote);
}