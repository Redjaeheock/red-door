/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/19 20:00:29 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	search_special_characters(char *str, int equal)
{
	int	i;

	i = 0;
	if (is_valid_var_name(str, equal) == 0)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '!' || str[i] == '#')
		{
			printf("bash: export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
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

int	check_key(t_path **old_exp, t_path *export_add)
{
	t_path	*temp;
	t_path	*prev;

	temp = *old_exp;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, export_add->key) == 0)
		{
			update_node(old_exp, prev, temp, export_add);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

int	search_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	process_export_entry(t_data *meta, \
	t_path *export_add, t_path *env_add, int equal)
{
	if (equal != 0)
	{
		if (check_key(&meta->exp, export_add) == 0)
			add_back_export_linked_list(&meta->exp, export_add);
		if (check_key(&meta->env, env_add) == 0)
			add_back_export_linked_list(&meta->env, env_add);
	}
	else
	{
		if (check_key(&meta->exp, export_add) == 0)
			add_back_export_linked_list(&meta->exp, export_add);
		free_t_path(env_add);
	}
}
