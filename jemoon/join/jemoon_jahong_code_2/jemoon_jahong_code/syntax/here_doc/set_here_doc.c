/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/19 20:37:13 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	set_here_doc(t_list **tokens)
{
	t_list	*tmp;

	tmp = *tokens;
	while ((*tokens) != NULL)
	{
		if ((*tokens)->type == HEREDOC)
		{
			*tokens = (*tokens)->next;
			here_doc(*tokens);
		}
		else
			*tokens = (*tokens)->next;
	}
	*tokens = tmp;
}
