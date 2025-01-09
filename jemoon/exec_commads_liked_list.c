/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_liked_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:13:18 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/09 11:28:51 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_exec_linked_list(t_cmd_list *list)
{
	t_cmd_list	*temp;
	int			i;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		i = 0;
		while (temp->str[i] != NULL)
		{
			free(temp->str[i]);
			i++;
		}
		free(temp->str);
		free(temp);
	}
}

t_cmd_list	*create_exec_linked_list(char **str)
{
	t_cmd_list	*new;

	new = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->type_pipe = NONE;
	new->type_re = NONE;
	new->next = NULL;
	return (new);
}
void	add_back_exec_linked_list(t_cmd_list **exec_commads, t_cmd_list *new)
{
	t_cmd_list	*temp;

	temp = *exec_commads;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	exec_make_node(t_cmd_list **exec_commads, char **string_array)
{
	t_cmd_list	*new_node;

	new_node = create_exec_linked_list(string_array);
	if (new_node == NULL)
		return (free_exec_linked_list(new_node));
	if (*exec_commads == NULL)
		*exec_commads = new_node;
	else
		add_back_exec_linked_list(exec_commads, new_node);

}
