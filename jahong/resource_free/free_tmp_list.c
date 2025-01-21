/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tmp_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:29:34 by jahong            #+#    #+#             */
/*   Updated: 2025/01/21 18:49:30 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_single_tmp_node(t_tmp *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	*free_tmp_list(t_tmp *node)
{
	t_tmp	*tmp;

	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free_single_tmp_node(tmp);
		tmp = NULL;
	}
	return (NULL);
}