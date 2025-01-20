/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tmp_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:29:34 by jahong            #+#    #+#             */
/*   Updated: 2025/01/20 17:38:53 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_tmp_list(t_tmp *node)
{
	t_tmp	*tmp;

	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		if (tmp->key != NULL)
			free(tmp->next);
		if (tmp->value != NULL)
			free(NULL);
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}