/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_tmp_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:26:55 by jahong            #+#    #+#             */
/*   Updated: 2025/01/31 16:58:53 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tmp	*last_tmp_list(t_tmp *node)
{
	t_tmp	*tmp;

	if (node == NULL)
		return (NULL);
	tmp = node;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	add_back_tmp_list(t_tmp *node, t_tmp *new)
{
	t_tmp	*temp;

	temp = last_tmp_list(node);
	temp->next = new;
	return ;
}

t_tmp	*create_new_tmp_list(char *str1, char *str2)
{
	t_tmp	*new;

	new = (t_tmp *)malloc(sizeof(t_tmp));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->key = str1;
	new->value = str2;
	return (new);
}

t_tmp	*make_tmp_node(t_tmp *node, char *str1, char *str2)
{
	t_tmp	*new_node;

	new_node = create_new_tmp_list(str1, str2);
	if (new_node == NULL)
		return (t_list_alloc_err(NULL));
	if (node == NULL)
		node = new_node;
	else
		add_back_tmp_list(node, new_node);
	return (node);
}