/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:01 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 14:23:29 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_index_range_jump_quote(char *str, int idx, int end)
{
	char	*copy;
	int		len;
	int		n;

	n = 0;
	len = quote_set_jump_len(str);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (memory_alloc_error());
	while (idx < end)
	{
		if (str[idx] == '\'' || str[idx] == '"')
		{
			idx++;
			continue ;
		}
		copy[n] = str[idx];
		n++;
		idx++;
	}
	copy[n] = '\0';
	return (copy);
}

char	**remove_all_same_str(char **str, char c)
{
	char	**keep;
	int		row;
	int		len;

	row = 0;
	len = count_only_single_chr_value_in_2d_arr(str, row, c);
	keep = (char **)malloc(sizeof(char *) * (len + 1));
	if (keep == NULL)
		return (memory_alloc_error());
	len = 0;
	while (str[row] != 0)
	{
		if (are_all_characters_same(str[row], c) == 0)
		{
			keep[len] = ft_strdup(str[row]);
			if (keep[len] == NULL)
				return (sndry_alloc_err((void **)keep));
			len++;
		}
		row++;
	}
	keep[len] = NULL;
	return (keep);
}

int	cnt_valid_split_point_chr_in_quote_set(char *path, char c, int quote)
{
	int	idx;
	int	cnt;

	idx = 0;
	cnt = 0;
	while (path[idx] != '\0')
	{
		cnt++;
		if (path[idx] == c)
			while (path[idx] == c && path[idx] != '\0')
				idx++;
		else
		{
			while (path[idx] != '\0')
			{
				if (path[idx] == '\'' || path[idx] == '"')
					quote = check_quote_pair(path[idx], quote);
				if (quote == 0 && path[idx] == c)
					break;
				idx++;
			}
		}
	}
	return (cnt);
}
