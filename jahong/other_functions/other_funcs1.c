/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_funcs1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:21:05 by jahong            #+#    #+#             */
/*   Updated: 2025/02/01 11:08:57 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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