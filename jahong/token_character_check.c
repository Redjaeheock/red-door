/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_character_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:40:39 by jahong            #+#    #+#             */
/*   Updated: 2025/01/19 01:59:17 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_wildcard(char *str, int idx, int quote)
{
	int	flag;
	int	cnt;

	flag = 1;
	cnt = 0;
	while (str[idx] != '\0' && str[idx] != ' ' && str[idx] != '\"')
	{
		if (str[idx] == '*')
			cnt++;
		else
			flag = 0;
		idx++;
	}
	if (quote == 2 && cnt >= 1 )
		return (1);
	if (quote == 0)
	{
		if (flag == 1 && cnt >= 1)
			return (1);
		if (flag == 0 && cnt >= 1)
			return (1);
	}
	return (0);
}
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