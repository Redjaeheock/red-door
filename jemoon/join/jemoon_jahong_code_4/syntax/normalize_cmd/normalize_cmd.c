/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/26 19:58:27 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

t_cmd_list	*cmd_temp_searching(t_cmd_list *temp)
{
	while (temp != NULL)
	{
		if (temp->type_pipe == NONE && temp->type_re == NONE && \
		(!temp->prev || temp->prev->type_re == NONE))
		{
			return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}

t_cmd_list	*get_cmd_node(t_cmd_list **check_temp)
{
	t_cmd_list	*return_temp;
	t_cmd_list	*front_temp;
	t_cmd_list	*next_temp;

	front_temp = NULL;
	next_temp = NULL;
	return_temp = cmd_temp_searching(*check_temp);
	if (return_temp == NULL)
		return (NULL);
	if (return_temp->next != NULL)
		*check_temp = return_temp->next;
	if (return_temp->prev != NULL)
		front_temp = return_temp->prev;
	if (return_temp->next != NULL)
		next_temp = return_temp->next;
	return_temp->next = NULL;
	front_temp->next = next_temp;
	return (return_temp);
}

void	cmd_merge(t_cmd_list *temp, t_cmd_list *add_temp)
{
	char	**temp_2d_arr;

	temp_2d_arr = ft_merge_2d_arr(temp->str, add_temp->str);
	free_exec_linked_list(add_temp);
	add_temp = NULL;
	free_sndry_arr((void **)temp->str);
	temp->str = NULL;
	temp->str = temp_2d_arr;
}

void	normalize_cmd(t_data *meta)
{
	t_cmd_list	*temp;
	t_cmd_list	*check_temp;
	t_cmd_list	*add_temp;

	temp = meta->exec_cmd;
	while (temp)
	{
		temp = cmd_temp_searching(temp);
		if (temp == NULL || temp->next == NULL)
			return ;
		check_temp = temp->next;
		while (check_temp != NULL && \
			!(AND <= check_temp->type_pipe && check_temp->type_pipe <= PIPE))
		{
			add_temp = get_cmd_node(&check_temp);
			if (add_temp != NULL)
				cmd_merge(temp, add_temp);
			else
				check_temp = NULL;
		}
		temp = temp->next;
	}
}
