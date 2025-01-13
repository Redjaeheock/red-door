/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_character_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:03:57 by jahong            #+#    #+#             */
/*   Updated: 2025/01/13 16:59:36 by jahong           ###   ########.fr       */
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