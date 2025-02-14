/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dividing_sub_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:34:43 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 18:45:23 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_partial_token(char *str, int idx, int *end, int *quote)
{
	char	*tmp;
	int		len;
	int		i;

	len = *end - idx;
	if (*end != ft_strlen(str))
		len++;
	i = 0;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (idx <= *end && str[idx] != '\0')
	{
		tmp[i] = str[idx];
		i++;
		idx++;
	}
	tmp[i] = '\0';
	*quote = check_quote_pair(str[*end], *quote);
	if (*quote == 0)
		*end += 1;
	return (tmp);
}

char	*temporary_div_token(char *str, int *idx, int *quote)
{
	char	*tmp;
	int		start;

	start = *idx;
	while (str[*idx] != '\0')
	{
		if (*quote == 0 && check_quote_pair(str[*idx + 1], *quote) != 0)
			break ;
		else if (*quote == 1 && check_quote_pair(str[*idx + 1], *quote) == 0)
		{
			*idx += 1;
			break ;
		}
		else if (*quote == 2 && check_quote_pair(str[*idx + 1], *quote) == 0)
		{
			*idx += 1;
			break ;
		}
		*idx += 1;
	}
	tmp = extract_partial_token(str, start, idx, quote);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	**dividing_sub_token(char *str, int len)
{
	char	**tmp;
	int		row;
	int		idx;
	int		quote;

	row = 0;
	idx = 0;
	quote = 0;
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (row < len)
	{
		quote = check_quote_pair(str[idx], quote);
		tmp[row] = temporary_div_token(str, &idx, &quote);
		if (tmp[row] == NULL)
			return (free_sndry_arr((void **)tmp));
		row++;
	}
	tmp[row] = NULL;
	return (tmp);
}
