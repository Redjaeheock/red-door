/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dividing_copied_token2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:54:01 by jahong            #+#    #+#             */
/*   Updated: 2025/01/25 09:15:35 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int   cmp_pre_next_chr(char *str, int idx)
{
	if (idx > 0)
	{
		if (ft_isalnum(str[idx - 1]) != 0 || str[idx - 1] == '_')
		{
			if (str[idx] == '*')
				return (1);
			if (str[idx] == '?')
				return (1);
		}
	}
	return (0);
}
int   increase_index(char *str, int idx)
{
	if (str[idx] == '$' && str[idx - 1] == '$')
		return (1);
	if (cmp_pre_next_chr(str, idx) != 0)
		return (2);
	if (check_valid_back(str, idx) != 0)
		return (1);
	if (check_quote_pair(str[idx], 0) != 0 || str[idx] == ' ')
		return (2);
	if (ck_part_of_special_chr(str[idx]) != 0)
		return (2);
   return (0);
}

int   move_index(char *str, int idx, int num)
{
	int inc_idx;

	inc_idx = 0;
    while ((num == 1) && str[idx] != '$' && str[idx] != '\0')
	{
        idx++;
	}
	if (num == 2)
	{
		idx++;
		while (str[idx] != '\0')
		{
			inc_idx = increase_index(str, idx);
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
char	*split_copied_token(char *str, int *idx, int *quote)
{
	char	*tmp;
	int		start;

	start = *idx;
	if (str[*idx] != '$')
		*idx = move_index(str, *idx, 1);
	else
		*idx = move_index(str, *idx, 2);
	if (*quote != 0 && str[*idx - 1] == '"')
	{
		if (*idx == ft_strlen(str))
			*idx -= 1;
	}
	*quote = check_quote_pair(str[*idx], *quote);
	printf(">>>>>>>>>>>>>>>>> start = %d | *idx = %d\n", start, *idx);
	tmp = copy_index_range(str, start, *idx);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
t_tmp	*dividing_copied_token(char *str)
{
	t_tmp	*tmp;
	int		idx;
	int		quote;

	idx = 0;
	tmp = NULL;
	quote = check_quote_pair(str[idx], 0);
	while (str[idx] != '\0')
	{
		tmp = make_tmp_node(tmp, split_copied_token(str, &idx, &quote), NULL);
		if (tmp == NULL)
			return (free_tmp_list(tmp));
	}
	return (tmp);
}