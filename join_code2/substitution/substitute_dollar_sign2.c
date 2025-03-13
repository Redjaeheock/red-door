/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_dollar_sign2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:44:30 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 18:12:12 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increase_value_of_vars_v3(char *str, int *idx, int *cnt, int *flag)
{
	if (check_quote_pair(str[*idx], 0) != 0)
		*cnt += 1;
	else if (str[*idx] == ' ' || ck_part_of_special_chr(str[*idx]) != 0)
	{
		*cnt += 1;
		*flag = 0;
	}
	else if (check_valid_back(str, *idx) != 0)
	{
		*cnt += 1;
		*flag = 2;
	}
}

void	increase_value_of_vars_v2(char *str, int *idx, int *cnt, int *flag)
{
	*cnt += 1;
	*flag = 1;
	if (str[*idx + 1] == '$' || check_valid_back(str, *idx + 1) != 0)
	{
		*idx += 1;
		*flag = 2;
	}
}

void	increase_value_of_vars_v1(int *cnt, int *flag)
{
	*cnt += 1;
	*flag = 0;
}

int	check_split_point_str(char *str)
{
	int		cnt;
	int		idx;
	int		flag;

	cnt = 0;
	idx = 0;
	flag = 2;
	while (str[idx] != '\0')
	{
		if (str[idx] != '$' && flag == 2)
			increase_value_of_vars_v1(&cnt, &flag);
		else if (str[idx] == '$')
			increase_value_of_vars_v2(str, &idx, &cnt, &flag);
		else if (flag == 1)
			increase_value_of_vars_v3(str, &idx, &cnt, &flag);
		idx++;
	}
	return (cnt);
	// 줄 수 조정
}
