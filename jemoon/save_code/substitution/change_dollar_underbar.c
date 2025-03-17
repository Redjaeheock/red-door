/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dollar_underbar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:01:02 by jahong            #+#    #+#             */
/*   Updated: 2025/03/13 18:00:04 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_dollar_underbar(t_data *meta, t_cmd_list *exec_cmd)
{
	t_path	*tmp;
	char	*keep;

	keep = exec_cmd->str[sndry_arr_len((void **)exec_cmd->str) - 1];
	tmp = meta->env;
	while (tmp != NULL)
	{
		if (ft_strcmp("_", tmp->key) == 0)
		{
			if (tmp->value != NULL)
				free(tmp->value);
			tmp->value = ft_strdup(keep);
			if (tmp->value == NULL)
				return ((memory_alloc_error(), 0));
			else
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
