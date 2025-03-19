/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest_plus_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:52:31 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/18 18:54:28 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	meta_plus_path_set(t_data *meta, char *str)
{
	t_path	*temp;

	temp = find_node_by_key(meta->env, str);
	if (ft_strcmp(temp->key, "PATH") == 0)
	{
		free_sndry_arr((void **)meta->path);
		meta->path = NULL;
		meta->path = extract_path(temp);
		if (meta->path == NULL)
			memory_alloc_error();
		path_set(meta, temp->set);
	}
	if (ft_strcmp(temp->key, "HOME") == 0)
	{
		free(meta->home);
		meta->home = NULL;
		meta->home = search_value_using_key(temp, "HOME");
		if (meta->home == NULL)
			memory_alloc_error();
	}
}

int	check_plus_key(t_data *meta, t_path **old_exp, \
	t_path *export_add, int equal)
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
			value_join_node(temp, export_add);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

void	process_plus_export_entry(t_data *meta, \
	t_path *export_add, t_path *env_add, int equal)
{
	char	*key_temp;

	key_temp = ft_strdup(env_add->key);
	if (key_temp == NULL)
		return ;
	if (equal != 0)
	{
		if (check_plus_key(meta, &meta->exp, export_add, equal) == 0)
			add_back_export_linked_list(&meta->exp, export_add);
		if (check_plus_key(meta, &meta->env, env_add, equal) == 0)
			add_back_export_linked_list(&meta->env, env_add);
	}
	else
	{
		if (check_plus_key(meta, &meta->exp, export_add, equal) == 0)
			add_back_export_linked_list(&meta->exp, export_add);
		free_t_path(env_add);
		env_add = NULL;
	}
	if (equal != 0 && key_temp != NULL)
		meta_plus_path_set(meta, key_temp);
	free(key_temp);
	key_temp = NULL;
}
