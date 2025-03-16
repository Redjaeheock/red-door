/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:45:22 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/31 11:06:06 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_node(t_path **exp, t_path *prev, t_path *current)
{
	if (prev == NULL)
	{
		*exp = current->next;
		current->next = NULL;
		free_key_value(current);
	}
	else
	{
		prev->next = current->next;
		current->next = NULL;
		free_key_value(current);
	}
}

int	unset_key(t_path **exp, char *str)
{
	t_path	*temp;
	t_path	*prev;

	temp = *exp;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, str) == 0)
		{
			remove_node(exp, prev, temp);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

void	unset_export(t_data *meta, int unset_len)
{
	int	i;

	i = 1;
	while (i < unset_len)
	{
		if (search_special_characters_unset(meta->exec_cmd->str[i]) == 1)
		{
			unset_key(&meta->exp, meta->exec_cmd->str[i]);
			unset_key(&meta->env, meta->exec_cmd->str[i]);
		}
		i++;
	}
}
