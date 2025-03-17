/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:34:29 by jahong            #+#    #+#             */
/*   Updated: 2025/01/31 10:27:38 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}
int	conditional_strlen(const char *s, unsigned char condition)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (0);
	while ((s[len] != condition) && (s[len] != '\0'))
		len++;
	return (len);
}

int	conditional_jump_len(const char *s, unsigned char condition)
{
	int	idx;
	int	len;

	idx = 0;
	len = 0;
	if (s == NULL)
		return (0);
	while (s[idx] != '\0')
	{
		if (s[idx] == condition)
			len++;
		idx++;
	}
	return (len);
}

int	quote_set_jump_len(const char *s)
{
	int	idx;
	int	quote;
	int	cnt;

	idx = 0;
	quote = 0;
	cnt = 0;
	if (s == NULL)
		return (0);
	while (s[idx] != '\0')
	{
		quote = check_quote_pair(s[idx], quote);
		if ((s[idx] == '\'' && quote == 1) || (s[idx] == '"' && quote == 2) ||
			(quote == 0 && (s[idx] == '"' || s[idx] == '\'')))
		{
			idx++;
			continue ;
		}
		idx++;
		cnt++;
	}
	return (cnt);
}
