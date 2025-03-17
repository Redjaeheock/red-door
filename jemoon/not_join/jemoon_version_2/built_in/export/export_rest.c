/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:43 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/01 15:23:23 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	search_special_characters(char *str)
{
	int	i;

	i = 0;
	while (('0' <= str[i] && str[i] <= '9') && str[i] != '\0')
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			printf("bash: export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	while (str[i] != '\0')
	{
		if (!(('A' <= str[i] && str[i] <= 'Z') || \
		('a' <= str[i] && str[i] <= 'z') || \
		('0' <= str[i] && str[i] <= '9') || \
		(str[i] == '_') || \
		(str[i] == '=' && i != 0)))
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
		new_node->next = current->next;
		current->next = NULL;
		free_key_value(current);
		*old_exp = new_node;
	}
	else
	{
		prev->next = new_node;
		new_node->next = current->next;
		current->next = NULL;
		free_key_value(current);
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
			return (1);
		i++;
	}
	return (0);
}

void	rest_export(t_data *meta, int export_len)
{
	int		i;
	int		equal;
	t_path	*export_add;

	i = 1;
	while (i < export_len)
	{
		equal = search_equal(meta->exec_cmd->str[i]);
		if (search_special_characters(meta->exec_cmd->str[i]) == 1)
		{
			export_add = add_export(meta->exec_cmd->str[i]);
			if (export_add == NULL)
				return ;
			if (equal == 1)
			{
				if (check_key(&meta->exp, export_add) == 0)
					add_back_export_linked_list(&meta->exp, export_add);
				if (check_key(&meta->env, export_add) == 0)
					add_back_export_linked_list(&meta->env, export_add);
			}
			else
			{
				if (check_key(&meta->exp, export_add) == 0)
					add_back_export_linked_list(&meta->exp, export_add);
			}
		}
		i++;
	}
}
