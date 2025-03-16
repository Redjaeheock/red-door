/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_funcs1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:21:05 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 18:56:44 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_only_single_chr_value_in_2d_arr(char **str, int row, char c)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[row] != NULL)
	{
		if (are_all_characters_same(str[row], c) == 0)
			len++;
		row++;
	}
	return (len);
}

int	is_token_all_null_after_join(t_tmp *tmp)
{
	int	cnt;
	int	cyc;

	cnt = 0;
	cyc = 0;
	while (tmp != NULL)
	{
		if (tmp->value == NULL)
			cnt++;
		tmp = tmp->next;
		cyc++;
	}
	if (cnt == cyc)
		return (1);
	return (0);
}
