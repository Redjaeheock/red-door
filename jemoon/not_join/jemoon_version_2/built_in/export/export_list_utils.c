/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:43:58 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/26 15:46:19 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize(t_path *lst)
{
	int		l_size;
	t_path	*temp;

	temp = lst;
	l_size = 0;
	while (temp)
	{
		l_size++;
		temp = temp->next;
	}
	return (l_size);
}

t_path	*add_export(char *str)
{
	t_path	*add_export_tokens;
	int		idx;

	idx = 0;
	add_export_tokens = make_t_path();
	if (add_export_tokens == NULL)
		return (NULL);
	if (extract_key_value(add_export_tokens, str, idx) != 1)
		return (t_path_key_val_alloc_err(add_export_tokens));
	return (add_export_tokens);
}

void	add_back_export_linked_list(t_path **old_export, t_path *new)
{
	t_path	*temp;

	temp = *old_export;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
}
