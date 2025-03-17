/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclusive_use_wildcard_split.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by jahong            #+#    #+#             */
/*   Updated: 2025/02/13 16:31:35 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	increase_idx_exclusive_use_wildcard_v2(char *src, int idx, int quote)
{
	if (src[idx] != '/' || (quote != 0 && src[idx] == '/'))
	{
		while (src[idx] != '\0')
		{
			if (src[idx] == '"' || src[idx] == '\'')
			{
				quote = check_quote_pair(src[idx], quote);
				if (quote != 0 && idx != 0 && src[idx - 1] == '*')
					break ;
			}
			if (quote == 0 && src[idx] == '/')
				break ;
			idx++;
		}
	}
	else
	{
		while (src[idx] == '/' && src[idx] != '\0')
			idx++;
	}
	return (idx);
}

char	**exclusive_use_wildcard_split1(char *src, int len, int row, int idx)
{
	char	**str;
	int		quote;
	int		start;

	start = 0;
	str = (char **)malloc(sizeof(char *) * (len + 1));
	if (str == NULL)
		return (NULL);
	quote = 0;
	while (src[idx] != '\0' && row < len)
	{
		idx = increase_idx_exclusive_use_wildcard_v2(src, idx, quote);
		str[row] = copy_index_range(src, start, idx);
		if (str[row] == NULL)
			return (NULL);
		start = idx;
		if (src[idx] == '"' && (quote == 0 || quote == 2))
			idx++;
		else if (src[idx] == '\'' && (quote == 0 || quote == 1))
			idx++;
		row++;
	}
	str[row] = NULL;
	return (str);
}

int	increase_idx_exclusive_use_wildcard(char *str, int idx, int quote)
{
	while (str[idx] != '\0')
	{
		if (str[idx] == '"' || str[idx] == '\'')
		{
			quote = check_quote_pair(str[idx], quote);
			if (quote != 0 && idx != 0 && str[idx - 1] == '*')
			{
				idx++;
				break ;
			}
		}
		if (quote == 0 && str[idx] == '/')
			break ;
		idx++;
	}
	return (idx);
}

int	exclusive_use_wildcard_len(char *str)
{
	int	idx;
	int	cnt;
	int	quote;

	idx = 0;
	cnt = 0;
	quote = 0;
	while (str[idx] != 0)
	{
		if (str[idx] != '/' || (quote != 0 && str[idx] == '/'))
		{
			cnt++;
			idx = increase_idx_exclusive_use_wildcard(str, idx, quote);
		}
		else
		{
			cnt++;
			while (str[idx] == '/' && str[idx] != '\0')
				idx++;
		}
	}
	return (cnt);
}
