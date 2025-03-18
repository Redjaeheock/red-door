/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:38:54 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/18 18:57:49 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

t_path	*find_node_by_key(t_path *list, char *key)
{
	while (list != NULL)
	{
		if (ft_strcmp(list->key, key) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	value_join_node(t_path *current, t_path *new_node)
{
	char	*tmp;

	tmp = ft_strdup(current->value);
	if (tmp == NULL)
		return ;
	free(current->value);
	current->value = NULL;
	current->value = ft_strjoin_v2(tmp, new_node->value);
	free(tmp);
	tmp = NULL;
	free_t_path(new_node);
	new_node = NULL;
	if (current->value == NULL)
		return ;
	tmp = ft_strjoin_v2(current->key, "=");
	if (tmp == NULL)
		return ;
	free(current->set);
	current->set = NULL;
	current->set = ft_strjoin_v2(tmp, current->value);
	free(tmp);
	tmp = NULL;
	if (current->set == NULL)
		return ;
}

void	oldpwd_plus_add(t_data *meta, t_path *export_add)
{
	char	*temp;

	if (ft_strcmp(export_add->key, "OLDPWD") == 0)
	{
		if (meta->oldpwd != NULL)
		{
			temp = ft_strdup(meta->oldpwd);
			if (temp == NULL)
				return ;
			free(meta->oldpwd);
			meta->oldpwd = NULL;
			meta->oldpwd = ft_strjoin_v2(temp, export_add->value);
			free(temp);
			temp = NULL;
			if (meta->oldpwd == NULL)
				return ;
		}
		else
			meta->oldpwd = ft_strdup(export_add->value);
	}
}

int	extract_plus_key_value(t_path *tmp, char *str)
{
	int		idx;
	int		start;
	char	*equla_join;

	idx = 0;
	start = idx;
	tmp->key = extract_from_envp(str, &idx, '+');
	idx++;
	tmp->value = extract_from_envp(str, &idx, '\0');
	if (tmp->key == NULL || tmp->value == NULL)
		return (0);
	equla_join = ft_strjoin_v2(tmp->key, "=");
	if (equla_join == NULL)
		return (0);
	tmp->set = ft_strjoin_v2(equla_join, tmp->value);
	if (tmp->set == NULL)
	{
		free(equla_join);
		return (0);
	}
	free(equla_join);
	equla_join = NULL;
	return (1);
}

t_path	*add_plus_export(char *str)
{
	t_path	*add_export_tokens;

	add_export_tokens = make_t_path();
	if (add_export_tokens == NULL)
		return (NULL);
	if (extract_plus_key_value(add_export_tokens, str) != 1)
		return (t_path_key_val_alloc_err(add_export_tokens));
	return (add_export_tokens);
}
