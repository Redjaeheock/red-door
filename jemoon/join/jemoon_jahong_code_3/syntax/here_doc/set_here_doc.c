/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/22 17:53:03 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	set_here_doc(t_data *meta)
{
	t_list	*tmp;

	tmp = meta->tokens;
	while (tmp != NULL)
	{
		if (tmp->type == HEREDOC)
		{
			meta->heredoc = 1;
			if (here_doc(meta, tmp->next) == 0)
			{
				if (meta->stdin_flag == -1)
					unlink_files(meta->tokens);
			}
			meta->heredoc = 0;
		}
		tmp = tmp->next;
	}

}


