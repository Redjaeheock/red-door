/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_str_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/14 17:59:40 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	operator_str_free(t_data *meta)
{
	t_cmd_list	*tmp;

	tmp = meta->exec_cmd;
	while (tmp != NULL)
	{
		if (tmp->str != NULL)
		{
			if (ft_strcmp(tmp->str[0], "<") == 0 || \
				ft_strcmp(tmp->str[0], "<<") == 0 || \
				ft_strcmp(tmp->str[0], ">") == 0 || \
				ft_strcmp(tmp->str[0], ">>") == 0 || \
				ft_strcmp(tmp->str[0], "|") == 0 || \
				ft_strcmp(tmp->str[0], "||") == 0 || \
				ft_strcmp(tmp->str[0], "&&") == 0)
			{
				free_sndry_arr((void **)tmp->str);
				tmp->str = NULL;
			}
		}
		tmp = tmp->next;
	}
}
