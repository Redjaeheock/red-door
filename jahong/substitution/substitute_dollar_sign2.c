/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_dollar_sign2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:44:30 by jahong            #+#    #+#             */
/*   Updated: 2025/02/01 13:50:32 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increase_value_of_vars(int *idx, int *cnt, int *flag, int *sign)
{
	if (*sign == 1)
	{
		*cnt += 1;
		*flag = 0;
	}
	else if (*sign == 2)
	{
		*cnt += 1;
		*flag = 1;
	}
	else if (*sign == 3)
	{
		*idx += 1;
		*flag = 2;
	}
	else if (*sign == 5)
	{
		*cnt += 1;
		*flag = 0;
	}
	else if (*sign == 6)
	{
		*cnt += 1;
		*flag = 2;
	}
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
		{
			cnt++;
			flag = 0;
		}	
		else if (str[idx] == '$')
		{
			cnt++;
			flag = 1;
			if (str[idx + 1] == '$' || check_valid_back(str, idx + 1) != 0)
			{
				idx++;	
				flag = 2;
			}
		}
		else if (flag == 1)
		{
			if (check_quote_pair(str[idx], 0) != 0)
				cnt++;
			else if (str[idx] == ' ' || ck_part_of_special_chr(str[idx]) != 0)
			{
				cnt++;
				flag = 0;
			}
			else if (check_valid_back(str, idx) != 0)
			{
				cnt++;
				flag = 2;
			}
		}
		idx++;
	}
	return (cnt);
	// 줄 수 조정
}