/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_liked_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:13:18 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/08 15:46:31 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	free_double_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_exec_linked_list(t_cmd_list *list)
{
	t_cmd_list	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		temp->prev = NULL;
		temp->next = NULL;
		if (temp->key != NULL)
			free(temp->key);
		if (temp->str != NULL)
			free_double_string_array(temp->str);
		free(temp);
		temp = NULL;
	}
	list = NULL;
}

t_cmd_list	*create_exec_linked_list(char **str, \
t_tokentype plag_pipe, t_tokentype plag_redi)
{
	t_cmd_list	*new;

	new = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (new == NULL)
		return (NULL);
	new->str = NULL;
	new->key = NULL;
	new->f_list = NULL;
	new->type_cmd = CMD;
	new->type_pipe = NONE;
	new->type_re = NONE;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_back_exec_linked_list(t_cmd_list **exec_cmd, \
t_cmd_list *new)
{
	t_cmd_list	*temp;

	temp = *exec_cmd;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}
