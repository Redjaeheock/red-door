/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_character_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:40:39 by jahong            #+#    #+#             */
/*   Updated: 2025/01/16 10:26:48 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int	check_token_chr(char *token, int idx)
{
	int	flag;

	flag = 0;
	if (token[idx] != '$')
		flag = 2;
	else if (token[idx] == '$')
	{
		flag = 0;
		if (token[idx + 1] == '$')
			flag = 1;
	}
	return (flag);
}