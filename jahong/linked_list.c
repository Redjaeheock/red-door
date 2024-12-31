/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:11:21 by jahong            #+#    #+#             */
/*   Updated: 2024/12/31 09:46:11 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_linked_list(t_list *list)
{
	t_list	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp->token);
		free(temp);
	}
}

t_list	*create_linked_list(char *str)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->token = str;
	new->next = NULL;
	return (new);
}

void	add_back_linked_list(t_list *tokenize, t_list *new)
{
	t_list	*temp;

	temp = tokenize;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	make_node(t_list **tokenize, char *str)
{
	t_list	*new_node;

	new_node = create_linked_list(str);
	if (new_node == NULL)
		return (free_linked_list(new_node));
	if (*tokenize == NULL)
		*tokenize = new_node;
	else
		add_back_linked_list(*tokenize, new_node);
}
