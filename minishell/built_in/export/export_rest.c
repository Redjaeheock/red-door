/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:43 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/18 15:49:12 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

/*
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


int	check_plus_key(t_data *meta, t_path **old_exp, t_path *export_add, int equal)
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
		meta_path_set(meta, env_add);
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
		meta_path_set(meta, key_temp);
	free(key_temp);
	key_temp = NULL;
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
		meta->oldpwd = ft_strdup(export_add->value);
	}
}

char	*extract_plus_from_envp(char *envp, int *idx, char condition)
{
	char	*str;
	int		col;
	int		len;

	col = 0;
	len = conditional_strlen(envp, condition);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while ((envp[*idx] != condition) && (envp[*idx] != '\0'))
	{
		str[col] = envp[*idx];
		*idx += 1;
		col++;
	}
	if (envp[*idx] != '\0')
		*idx += 1;
	str[col] = '\0';
	return (str);
}

int	extract_plus_key_value(t_path *tmp, char *str)
{
	int		idx;
	int		start;
	int		check_idx;
	char	*equla_join;

	idx = 0;
	check_idx = 0;
	start = idx;
	tmp->key = extract_plus_from_envp(str, &idx, '+');
	check_idx = idx;
	idx++;
	tmp->value = extract_plus_from_envp(str, &idx, '\0');
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
*/
void	rest_export(t_data *meta, t_cmd_list *exec_cmd, int export_len)
{
	int		i;
	int		equal;
	int		plus_check;
	t_path	*export_add;
	t_path	*env_add;

	i = 1;
	while (i < export_len)
	{
		equal = search_equal(exec_cmd->str[i]);
		plus_check = search_special_characters(exec_cmd->str[i], equal);
		if (plus_check != 0)
		{
			export_add = add_export(exec_cmd->str[i]);
			if (export_add == NULL)
				return ;
			env_add = add_export(exec_cmd->str[i]);
			if (env_add == NULL)
				return ;
			if (equal != 0)
				oldpwd_add(meta, export_add);
			process_export_entry(meta, export_add, env_add, equal);
		}
/*
		else if (plus_check == 2)
		{
			export_add = add_plus_export(exec_cmd->str[i]);
			if (export_add == NULL)
				return ;
			env_add = add_plus_export(exec_cmd->str[i]);
			if (env_add == NULL)
				return ;
			if (equal != 0)
				oldpwd_plus_add(meta, export_add);
			process_plus_export_entry(meta, export_add, env_add, equal);
		}
*/
		i++;
	}
}
