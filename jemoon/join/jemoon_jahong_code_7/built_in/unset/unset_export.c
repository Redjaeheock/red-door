/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:45:22 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 00:48:05 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	remove_node(t_path **exp, t_path *prev, t_path *current)
{
	if (prev == NULL)
	{
		*exp = current->next;
	}
	else
	{
		prev->next = current->next;
	}
	current->next = NULL;
	free_t_path(current);
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

void	unset_meta_date(t_data *meta, char *str)
{
	if (ft_strcmp(str, "PATH") == 0)
	{
		free_sndry_arr((void **)meta->path);
		meta->path = NULL;
	}
	if (ft_strcmp(str, "OLDPWD") == 0)
	{
		free(meta->oldpwd);
		meta->oldpwd = NULL;
	}
}

void	unset_export(t_data *meta, t_cmd_list *exec_cmd, int unset_len)
{
	int	i;

	i = 1;
	while (i < unset_len)
	{
		if (ft_strcmp(exec_cmd->str[i], "_") == 0)
		{
			i++;
			continue ;
		}
		if (check_option(exec_cmd->str[1]) == 1)
			return (builtin_error(exec_cmd->str[1], 62));
		unset_key(&meta->exp, exec_cmd->str[i]);
		unset_key(&meta->env, exec_cmd->str[i]);
		unset_meta_date(meta, exec_cmd->str[i]);
		i++;
	}
}
