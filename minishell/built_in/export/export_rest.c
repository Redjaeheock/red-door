/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:43 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 23:08:19 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

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
		if (plus_check == 1)
		{
			export_add = add_export(exec_cmd->str[i]);
			if (export_add == NULL)
				return ;
			env_add = add_export(exec_cmd->str[i]);
			if (env_add == NULL)
				return ;
			oldpwd_add(meta, export_add);
			process_export_entry(meta, export_add, env_add, equal);
		}
		else if (plus_check == 2)
		{
			export_add = add_plus_export(exec_cmd->str[i]);
			if (export_add == NULL)
				return ;
			env_add = add_plus_export(exec_cmd->str[i]);
			if (env_add == NULL)
				return ;
		}
		i++;
	}
}
