/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dollar_underbar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:01:02 by jahong            #+#    #+#             */
/*   Updated: 2025/03/14 18:02:36 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_dollar_underbar(t_data *meta, t_cmd_list *exec_cmd)
{
	t_path	*tmp;
	char	*keep;

	//printf("check = [%s]\n", exec_cmd->str[0]);
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
