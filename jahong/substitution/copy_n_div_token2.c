/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_n_div_token2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:03:17 by jahong            #+#    #+#             */
/*   Updated: 2025/01/19 02:19:48 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// v1 파일 삭제하기

int   cmp_pre_next_chr(char *str, int idx)
{
	if (idx > 0)
	{
		if (ft_isalnum(str[idx - 1]) != 0 || str[idx - 1] == '_')
		{
			if (str[idx] == '*')
				return (1);
		}
	}
	return (0);
}
int   increase_index(char *str, int idx, int quote)
{

	if (str[idx] == '$' && str[idx - 1] == '$')
		return (1);
	if (cmp_pre_next_chr(str, idx) != 0)
		return (2);
	if (check_valid_back(str, idx) != 0)
		return (1);
	if (check_quote_pair(str[idx], 0) != 0 || str[idx] == ' ')
		return (2);
	if (ft_isspecial_chr(str[idx]) != 0)
		return (2);
   return (0);
}

int   move_index(char *str, int idx, int quote, int num)
{
	int inc_idx;

	inc_idx = 0;
    while (num == 1 && str[idx] != '$' && str[idx] != '\0')
        idx++;
	if (num == 2)
	{
		idx++;
		while (str[idx] != '\0')
		{
			inc_idx = increase_index(str, idx, quote);
			if (inc_idx == 1)
			{
				idx += inc_idx;
				break ;
			}
			else if (inc_idx == 2)
				break ;
			idx++;
			inc_idx = 0;
		}
	}
	return (idx);
}
char	*split_token(char *str, int *idx, int quote)
{
	char	*tmp;
	int		start;

	start = *idx;
	if (str[*idx] != '$')
		*idx = move_index(str, *idx, quote, 1);
	else
		*idx = move_index(str, *idx, quote, 2);
	printf("start = %d *idx = %d\n", start, *idx);
	tmp = copy_split_token(str, start, *idx);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
char	**div_copy_token(char *str, int len, int quote)
{
	char	**tmp;
	int		row;
	int		idx;

	row = 0;
	idx = 0;
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (row < len)
	{
		tmp[row] = split_token(str, &idx, quote);
		if (tmp[row] == NULL)
			return (sndry_alloc_err((void **)tmp));
		row++;
	}
	tmp[row] = NULL;
	return (tmp);
}