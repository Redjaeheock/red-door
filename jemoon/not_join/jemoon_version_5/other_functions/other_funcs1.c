/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_funcs1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:21:05 by jahong            #+#    #+#             */
/*   Updated: 2025/01/31 15:07:23 by jahong           ###   ########.fr       */
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

char	*copy_quote_set_jump(char *s, char *tmp, int len)
{
	int		quote;
	int		idx;
	int		n;

	quote = 0;
	idx = 0;
	n = 0;
	while (s[idx] != '\0')
	{
		quote = check_quote_pair(s[idx], quote);
		if ((s[idx] == '\'' && quote == 1) || (s[idx] == '"' && quote == 2) ||
			(quote == 0 && (s[idx] == '"' || s[idx] == '\'')))
		{
			idx++;
			continue ;
		}
		tmp[n] = s[idx];
		n++;
		idx++;
	}
	tmp[n] = '\0';
	return (tmp);
}
