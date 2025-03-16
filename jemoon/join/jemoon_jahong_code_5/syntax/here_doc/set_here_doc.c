/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/26 19:59:34 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	out_here_doc(t_data *meta)
{
	meta->heredoc = -1;
	meta->stdin_flag = 0;
	meta->tokens = free_t_list(meta->tokens);
}

void	set_here_doc(t_data *meta, t_list *tmp)
{
	while (tmp != NULL)
	{
		if (tmp->type == HEREDOC && meta->heredoc != -1)
		{
			meta->heredoc = 1;
			if (tmp->next == NULL)
			{
				meta->heredoc = 0;
				return ;
			}
			if (here_doc(meta, tmp->next) == 0)
			{
				if (meta->stdin_flag == -1)
				{
					unlink_files(tmp);
					out_here_doc(meta);
					return ;
				}
			}
			else
				meta->heredoc = 0;
		}
		tmp = tmp->next;
	}
}
