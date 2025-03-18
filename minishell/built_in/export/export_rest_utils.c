/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 20:23:05 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	oldpwd_add(t_data *meta, t_path *export_add)
{
	if (ft_strcmp(export_add->key, "OLDPWD") == 0)
	{
		if (meta->oldpwd != NULL)
		{
			free(meta->oldpwd);
			meta->oldpwd = NULL;
		}
		meta->oldpwd = ft_strdup(export_add->value);
	}
}

void	update_node(t_path **old_exp, t_path *prev,
t_path *current, t_path *new_node)
{
	if (prev == NULL)
	{
		new_node->next = (*old_exp)->next;
		current->next = NULL;
		*old_exp = new_node;
		free_t_path(current);
	}
	else
	{
		prev->next = new_node;
		new_node->next = current->next;
		current->next = NULL;
		free_t_path(current);
	}
}

int	check_key(t_data *meta, t_path **old_exp, t_path *export_add, int equal)
{
	t_path	*temp;
	t_path	*prev;

	temp = *old_exp;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, export_add->key) == 0)
		{
			if (equal == 0)
			{
				free_t_path(export_add);
				export_add = NULL;
				return (1);
			}
			update_node(old_exp, prev, temp, export_add);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

void	process_export_entry(t_data *meta, \
	t_path *export_add, t_path *env_add, int equal)
{
	if (equal != 0)
	{
		if (check_key(meta, &meta->exp, export_add, equal) == 0)
			add_back_export_linked_list(&meta->exp, export_add);
		if (check_key(meta, &meta->env, env_add, equal) == 0)
			add_back_export_linked_list(&meta->env, env_add);
	}
	else
	{
		if (check_key(meta, &meta->exp, export_add, equal) == 0)
			add_back_export_linked_list(&meta->exp, export_add);
		free_t_path(env_add);
		env_add = NULL;
	}
	if (env_add != NULL)
	{
		meta_path_set(meta, env_add);
	}
}
