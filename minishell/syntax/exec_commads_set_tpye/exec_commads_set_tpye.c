/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_set_tpye.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:41:02 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/16 12:06:09 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	exec_cmd_set_type(t_data *meta)
{
	t_cmd_list	*tmp;

	tmp = meta->exec_cmd;
	while (tmp)
	{
		if (is_cmd_branch(tmp))
		{
			if (tmp->type_pipe == PIPE && tmp->str == NULL)
			{
				if (check_prev(tmp))
					tmp->prev->type_pipe = tmp->type_pipe;
				if (check_next(tmp))
					tmp->next->type_pipe = tmp->type_pipe;
			}
			tmp->type_cmd = NONE;
		}
		else if (check_redi(tmp))
		{
			tmp->type_cmd = NONE;
			if (check_next(tmp))
				tmp->next->type_cmd = NONE;
		}
		tmp = tmp->next;
	}
}
