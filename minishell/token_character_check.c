/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_character_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:40:39 by jahong            #+#    #+#             */
/*   Updated: 2025/03/21 23:43:46 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_back(char *str, int idx)
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

int	count_quote_set(t_list *tokens, char c)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (c == 'c')
		{
			if (check_quote_valid(tmp->token) == 0)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
