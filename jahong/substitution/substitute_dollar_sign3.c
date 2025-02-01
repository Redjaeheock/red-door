/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_dollar_sign3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:24:49 by jahong            #+#    #+#             */
/*   Updated: 2025/02/01 14:04:39 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	choice_null_case(t_tmp *node)
{
	if ((node->key[0] == '$' && node->key[1] != '\0'))
		node->value = NULL;
	else if (are_all_characters_same(node->key, '*') == 1)
		node->value = NULL;
	else
	{
		node->value = ft_strdup(node->key);
		if (node->value == NULL)
			return ((memory_alloc_error(), 0));
	}
	return (1);
}

int	check_except_substitution(t_tmp	*node)
{
	if (node->key == NULL)
		return (1);
	if (ft_strcmp(node->key, "$$") == 0)
	{
		node->value = copy_current_process_pid();
		if (node->value == NULL)
			return (-1);
		return (1);
	}
	if (ft_strcmp(node->key, "$?") == 0)
	{
		node->value = get_exit_no();
		if (node->value == NULL)
			return (-1);
		return (1);
	}
	return (0);
}

int	search_in_envpath(t_data *meta, t_tmp*node)
{
	t_path	*tmp;
	int		result;

	tmp = meta->env;
	result = check_except_substitution(node);
	if (result != 0)
		return (result);
	while (tmp != NULL)
	{
		if (ft_strcmp(&node->key[1], tmp->key) == 0)
		{
			node->value = "";
			node->value =  ft_strdup(tmp->value);
			if (node->value == NULL)
				return (-1);
		}
		tmp = tmp->next;
	}
	// node->value = search_value_using_key(meta->env, &node->key[1]);
	// if (node->value == NULL)
	// 	return (-1);
	if (node->value == NULL && node->key[0] != '"')
	{
		result = choice_null_case(node);
		if (result == 0)
			return (-1);
	}
	return (1);
}

int	mapping_dollar_sign_to_env(t_data *meta, t_tmp *node)
{
	t_tmp	*tmp;
	int		result;

	tmp = node;
	while (tmp != NULL)
	{
		result = search_in_envpath(meta, tmp);
		if (result == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}

t_tmp	*change_dollar_sign(t_data *meta, char *str)
{
	t_tmp	*tmp;
	int		result;
	t_tmp	*keep;

	tmp = dividing_copied_token(str);
	if (tmp == NULL)
		return (NULL);
	result = mapping_dollar_sign_to_env(meta, tmp);
	if (result == -1)
		return (free_tmp_list(tmp));
	keep = tmp;
	while (keep != NULL)
	{
		if (keep->key != NULL)
			printf("keep key =  %s\n", keep->key);
		if (keep->value != NULL)
			printf("keep value =  %s\n", keep->value);
		keep = keep->next;
	}
	
	return (tmp);
}