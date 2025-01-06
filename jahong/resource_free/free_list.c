/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:36:52 by jahong            #+#    #+#             */
/*   Updated: 2025/01/06 16:45:44 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_t_path(t_path	*list)
{
	t_path	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
	return (NULL);
}


void	*free_t_list(t_list *list)
{
	t_list	*temp;

	// 구조체 멤버 해제 후 리스트 해제제

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		temp->prev = NULL;
		free(temp->token);
		free(temp);
	}
	return (NULL);
}